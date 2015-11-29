//
//  Board.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Board.h"

#include <iostream>

using Value = Cell::Value;

const int Board::ROWS = 7;
const int Board::COLS = 7;

const Value DEFAULT_LAYOUT[7][7] = {
    {Value::invalid, Value::invalid, Value::fox, Value::empty, Value::fox, Value::invalid, Value::invalid},
    {Value::invalid, Value::invalid, Value::empty, Value::empty, Value::empty, Value::invalid, Value::invalid},
    {Value::empty, Value::empty, Value::empty, Value::empty, Value::empty, Value::empty, Value::empty},
    {Value::sheep, Value::sheep, Value::sheep, Value::sheep, Value::sheep, Value::sheep, Value::sheep},
    {Value::sheep, Value::sheep, Value::sheep, Value::sheep, Value::sheep, Value::sheep, Value::sheep},
    {Value::invalid, Value::invalid, Value::sheep, Value::sheep, Value::sheep, Value::invalid, Value::invalid},
    {Value::invalid, Value::invalid, Value::sheep, Value::sheep, Value::sheep, Value::invalid, Value::invalid}
};

Board::Board() {
    for (int row = 0; row < ROWS; row++) {
        layout.push_back(std::vector<Cell>());
        for (int column = 0; column < COLS; column++) {
            layout[row].push_back(Cell(row, column, DEFAULT_LAYOUT[row][column]));
        }
    }
}

Board::Board(char layout[7][7]) {
    for (int row = 0; row < ROWS; row++) {
        this->layout.push_back(std::vector<Cell>());
        for (int column = 0; column < COLS; column++) {
            this->layout[row].push_back(Cell(row, column, layout[row][column]));
        }
    }
}

// Big 3
Board::Board(const Board &board) : layout(board.layout) {}

Board& Board::operator=(const Board &board) {
    if (this != &board) {
        layout = board.layout;
    }
    
    return *this;
}

Board::~Board() {}

Cell Board::getCellAtIndex(const int &x, const int &y) const {
    if (x < 0 || y < 0 || x >= ROWS || y >= COLS) {
        return layout[0][0];
    }
    return layout[x][y];
}

Cell Board::getCellInDirectionFromCellWithRadius(const Board::Direction &direction, const Cell &cell, const int &radius) const {
    Cell returnCell;
    switch (direction) {
        case up: {
            returnCell = getCellAtIndex(cell.getRow() - radius, cell.getColumn());
            break;
        }
        case down: {
            returnCell = getCellAtIndex(cell.getRow() + radius, cell.getColumn());
            break;
        }
        case left: {
            returnCell = getCellAtIndex(cell.getRow(), cell.getColumn() - radius);
            break;
        }
        case right: {
            returnCell = getCellAtIndex(cell.getRow(), cell.getColumn() + radius);
            break;
        }
        case upLeft: {
            returnCell = getCellAtIndex(cell.getRow() - radius, cell.getColumn() - radius);
            break;
        }
        case upRight: {
            returnCell = getCellAtIndex(cell.getRow() - radius, cell.getColumn() + radius);
            break;
        }
        case downLeft: {
            returnCell = getCellAtIndex(cell.getRow() + radius, cell.getColumn() - radius);
            break;
        }
        case downRight: {
            returnCell = getCellAtIndex(cell.getRow() + radius, cell.getColumn() + radius);
            break;
        }
    }
    
    return returnCell;
}

std::map<Board::Direction, Cell> Board::getSurroundingCells(Cell cell) {
    std::map<Board::Direction, Cell> cells;
    
    cellInDirection(cells, up, cell);
    cellInDirection(cells, down, cell);
    cellInDirection(cells, left, cell);
    cellInDirection(cells, right, cell);
    
    if (cell.isFox()) {
        if ((cell.getRow() % 2 == 0 && cell.getColumn() % 2 == 0) || (cell.getRow() % 2 != 0 && cell.getColumn() % 2 != 0)) {
            cellInDirection(cells, upLeft, cell);
            cellInDirection(cells, upRight, cell);
            cellInDirection(cells, downLeft, cell);
            cellInDirection(cells, downRight, cell);
        }
        
    }
    
    return cells;
}

void Board::cellInDirection(std::map<Board::Direction, Cell> &cells, const Board::Direction &direction, const Cell &cell) const {
    Cell cellInDirection = getCellInDirectionFromCellWithRadius(direction, cell);
    
    if (!cellInDirection.isInvalid()) {
        cells[direction] = cellInDirection;
    }
}

void Board::applyMove(const Move &move) {
    for (std::vector<Jump>::iterator iterator = move.getJumps().begin(); iterator != move.getJumps().end(); iterator++) {
        makeJump(Jump(*iterator));
    }
}

void Board::makeJump(const Jump &jump) {
    if (isValidJump(jump)) {
        if (jump.getStart() != jump.getEnd()) {
            layout[jump.getEnd().getRow()][jump.getEnd().getColumn()].setValue(jump.getStart().getValue());
            layout[jump.getStart().getRow()][jump.getStart().getColumn()].setValue(Cell::Value::empty);
            if (jump.isCaptureJump()) {
                layout[jump.getJumpedCell().getRow()][jump.getJumpedCell().getColumn()].setValue(Cell::Value::empty);
            }
        }
    }
}

bool Board::isValidMove(const Move &move) const {
    bool valid = false;
    Board board = *this;
    for (std::vector<Jump>::iterator iterator = move.getJumps().begin(); iterator != move.getJumps().end(); iterator++) {
        if (board.isValidJump(Jump(*iterator))) {
            board.makeJump(Jump(*iterator));
            valid = true;
        } else {
            valid = false;
        }
    }
    
    return valid;
}

bool Board::isValidJump(const Jump &jump) const {
    Cell start = jump.getStart();
    Cell end = jump.getEnd();
    bool valid = true;
    
    if (layout[start.getRow()][start.getColumn()].isSheep()) {
        if (layout[end.getRow()][end.getColumn()].isEmpty()) {
            // Sheep cannot move more than one space and only left, right, or up
            if (start.getColumn() - end.getColumn() > 1 || start.getColumn() - end.getColumn() < -1) {
                valid = false;
            } else if (start.getRow() - end.getRow() > 1 || start.getRow() < end.getRow()) {
                valid = false;
            } else if (start.getRow() - end.getRow() != 0 && start.getColumn() - end.getColumn() != 0) {
                // Cannot make a diagnol move
                valid = false;
            }
        } else {
            valid = false;
        }
    } else if (layout[start.getRow()][start.getColumn()].isFox()) {
        // Can only move along the lines on the board
        if ((start.getRow() % 2 == 0 && start.getColumn() % 2 != 0) || (start.getRow() % 2 != 0 && start.getColumn() % 2 == 0)) {
            if (start.getRow() != end.getRow() && start.getColumn() != end.getColumn()) {
                valid = false;
            }
        }
    }
    
    // Allow staying in the same place
    if (start == end) {
        valid = true;
    }
    
    return valid;
}

bool Board::isPaddockFull() const {
    
    if (layout[0][2].isSheep() &&
        layout[0][3].isSheep() &&
        layout[0][4].isSheep() &&
        layout[1][2].isSheep() &&
        layout[1][3].isSheep() &&
        layout[1][4].isSheep() &&
        layout[2][2].isSheep() &&
        layout[2][3].isSheep() &&
        layout[2][4].isSheep()) {
        return true;
    }
    
    return false;
}

int Board::sheepRemaining() const {
    int count = 0;
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            if (layout[row][column].isSheep()) {
                count++;
            }
        }
    }
    
    return count;
}

std::vector<Cell> Board::getFoxCells() const {
    std::vector<Cell> cells;
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            if (layout[row][column].isFox()) {
                cells.push_back(layout[row][column]);
            }
        }
    }
    return cells;
}

void Board::print(std::ostream &output) const {
    for (int i = 0; i < ROWS; i++) {
        output << ROWS - i << " ";
        for (int j = 0; j < COLS; j++) {
            Cell cell = layout[i][j];
            output << cell.getValue();
            if (!cell.isInvalid()) {
                if ((j + 1) < layout[i].size() && !layout[i][j + 1].isInvalid()) {
                    output << '-';
                }
            } else {
                output << Cell::Value::invalid;
            }
        }
        output << std::endl;
        if (i < 6) {
            output << printDirectionalLinesForRow(i) << std::endl;
        }
        
    }
    std::cout << "  a b c d e f g" << std::endl;
}

std::string Board::printDirectionalLinesForRow(int row) const {
    std::string result = "";
    switch (row) {
        case 0:
            result = "      |\\|/|    ";
            break;
        case 1:
            result = "      |/|\\|    ";
            break;
        case 2:
            result = "  |\\|/|\\|/|\\|/|";
            break;
        case 3:
            result = "  |/|\\|/|\\|/|\\|";
            break;
        case 4:
            result = "      |\\|/|    ";
            break;
        case 5:
            result = "      |/|\\|    ";
            break;
        default:
            break;
    }
    
    return result;
}
