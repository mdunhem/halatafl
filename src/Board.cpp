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

//const char DEFAULT_LAYOUT[7][7] = {
//    { INVALID_SPACE, INVALID_SPACE, FOX_CHARACTER, EMPTY_SPACE, FOX_CHARACTER, INVALID_SPACE, INVALID_SPACE},
//    { INVALID_SPACE, INVALID_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, INVALID_SPACE, INVALID_SPACE},
//    { EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
//    { SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER},
//    { SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER},
//    { INVALID_SPACE, INVALID_SPACE, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, INVALID_SPACE, INVALID_SPACE},
//    { INVALID_SPACE, INVALID_SPACE, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, INVALID_SPACE, INVALID_SPACE}
//};

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

Board::Board(const Board &board) {
    for (int row = 0; row < ROWS; row++) {
        layout.push_back(std::vector<Cell>());
        for (int column = 0; column < COLS; column++) {
            layout[row].push_back(board.layout[row][column]);
        }
    }
}

Cell Board::getCellAtIndex(int x, int y) {
    if (x < 0 || y < 0 || x >= ROWS || y >= COLS) {
        return layout[0][0];
    }
    return layout[x][y];
}

Cell Board::getCellInDirectionFromCellWithRadius(Board::Direction direction, Cell &cell, int radius) {
    Cell returnCell;
    switch (direction) {
        case up: {
            returnCell = getCellAtIndex(cell.row - radius, cell.column);
            break;
        }
        case down: {
            returnCell = getCellAtIndex(cell.row + radius, cell.column);
            break;
        }
        case left: {
            returnCell = getCellAtIndex(cell.row, cell.column - radius);
            break;
        }
        case right: {
            returnCell = getCellAtIndex(cell.row, cell.column + radius);
            break;
        }
        case upLeft: {
            returnCell = getCellAtIndex(cell.row - radius, cell.column - radius);
            break;
        }
        case upRight: {
            returnCell = getCellAtIndex(cell.row - radius, cell.column + radius);
            break;
        }
        case downLeft: {
            returnCell = getCellAtIndex(cell.row + radius, cell.column - radius);
            break;
        }
        case downRight: {
            returnCell = getCellAtIndex(cell.row + radius, cell.column + radius);
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
        if ((cell.row % 2 == 0 && cell.column % 2 == 0) || (cell.row % 2 != 0 && cell.column % 2 != 0)) {
            cellInDirection(cells, upLeft, cell);
            cellInDirection(cells, upRight, cell);
            cellInDirection(cells, downLeft, cell);
            cellInDirection(cells, downRight, cell);
        }
        
    }
    
    return cells;
}

void Board::cellInDirection(std::map<Board::Direction, Cell> &cells, Board::Direction direction, Cell cell) {
    Cell cellInDirection = getCellInDirectionFromCellWithRadius(direction, cell);
    
    if (!cellInDirection.isInvalid()) {
        cells[direction] = cellInDirection;
    }
}

void Board::applyMove(Move move) {
    for (std::vector<Jump>::iterator iterator = move.jumps.begin(); iterator != move.jumps.end(); iterator++) {
        makeJump(Jump(*iterator));
    }
}

void Board::makeJump(Jump jump) {
    if (isValidJump(jump)) {
        if (jump.start != jump.end) {
            layout[jump.end.row][jump.end.column].value = jump.start.value;
            layout[jump.start.row][jump.start.column].value = Cell::Value::empty;
            if (jump.isCaptureJump()) {
                layout[jump.jumpedCell.row][jump.jumpedCell.column].value = Cell::Value::empty;
            }
        }
    }
}

bool Board::isValidMove(Move move) {
    bool valid = false;
    Board board = *this;
    for (std::vector<Jump>::iterator iterator = move.jumps.begin(); iterator != move.jumps.end(); iterator++) {
        if (board.isValidJump(Jump(*iterator))) {
            board.makeJump(Jump(*iterator));
            valid = true;
        } else {
            valid = false;
        }
    }
    
    return valid;
}

bool Board::isValidJump(Jump jump) {
    Cell *start = &jump.start;
    Cell *end = &jump.end;
    bool valid = true;
    
    if (layout[start->row][start->column].isSheep()) {
        if (layout[end->row][end->column].isEmpty()) {
            // Sheep cannot move more than one space and only left, right, or up
            if (start->column - end->column > 1 || start->column - end->column < -1) {
                valid = false;
            } else if (start->row - end->row > 1 || start->row < end->row) {
                valid = false;
            } else if (start->row - end->row != 0 && start->column - end->column != 0) {
                // Cannot make a diagnol move
                valid = false;
            }
        }
    } else if (layout[start->row][start->column].isFox()) {
        // Can only move along the lines on the board
        if ((start->row % 2 == 0 && start->column % 2 != 0) || (start->row % 2 != 0 && start->column % 2 == 0)) {
            if (start->row != end->row && start->column != end->column) {
                valid = false;
            }
        }
    }
    
    // Allow staying in the same place
    if (*start == *end) {
        valid = true;
    }
    
    return valid;
}

bool Board::isPaddockFull() {
    
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

int Board::sheepRemaining() {
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

std::vector<Cell> Board::getFoxCells() {
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
            output << cell.value;
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
