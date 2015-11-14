//
//  BoardLayout.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "BoardLayout.h"

#include <iostream>

const char DEFAULT_LAYOUT[7][7] = {
    { INVALID_SPACE, INVALID_SPACE, FOX_CHARACTER, EMPTY_SPACE, FOX_CHARACTER, INVALID_SPACE, INVALID_SPACE},
    { INVALID_SPACE, INVALID_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, INVALID_SPACE, INVALID_SPACE},
    { EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
    { SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER},
    { SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER},
    { INVALID_SPACE, INVALID_SPACE, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, INVALID_SPACE, INVALID_SPACE},
    { INVALID_SPACE, INVALID_SPACE, SHEEP_CHARACTER, SHEEP_CHARACTER, SHEEP_CHARACTER, INVALID_SPACE, INVALID_SPACE}
};

BoardLayout::BoardLayout() {
    for (int row = 0; row < 7; row++) {
        layout2.push_back(std::vector<Cell>());
        for (int column = 0; column < 7; column++) {
            layout[row][column] = DEFAULT_LAYOUT[row][column];
            layout2[row].push_back(Cell(row, column, DEFAULT_LAYOUT[row][column]));
        }
    }
}

BoardLayout::BoardLayout(char layout[7][7]) {
    for (int row = 0; row < 7; row++) {
        layout2.push_back(std::vector<Cell>());
        for (int column = 0; column < 7; column++) {
            this->layout[row][column] = layout[row][column];
            layout2[row].push_back(Cell(row, column, layout[row][column]));
        }
    }
}

BoardLayout::BoardLayout(const BoardLayout &boardLayout) {
    for (int row = 0; row < 7; row++) {
        layout2.push_back(std::vector<Cell>());
        for (int column = 0; column < 7; column++) {
            layout[row][column] = boardLayout.layout[row][column];
            layout2[row].push_back(boardLayout.layout2[row][column]);
        }
    }
}

char BoardLayout::getValueAt(Coordinate coordinate) {
    if (isValidCoordinate(coordinate)) {
        return layout[coordinate.row()][coordinate.column()];
    }
    return INVALID_SPACE;
}

Cell BoardLayout::getCellAtIndex(int x, int y) {
    return layout2[x][y];
}

std::vector<Cell> BoardLayout::cellsForRow(int row) {
    return layout2[row];
}

char* BoardLayout::operator[](int index) {
    return layout[index];
}

bool BoardLayout::isValidCoordinate(Coordinate coordinate) {
    if (coordinate.row() == -1 || coordinate.column() == -1) {
        return false;
    }
    if (layout[coordinate.row()][coordinate.column()] == INVALID_SPACE) {
        return false;
    }
    
    return true;
}

bool BoardLayout::applyMove(Move move) {
    for (std::vector<Jump>::iterator iterator = move.jumps.begin(); iterator != move.jumps.end(); iterator++) {
        Coordinate start = Jump(*iterator).start;
        Coordinate end = Jump(*iterator).end;
        
        if (layout[end.row()][end.column()] == INVALID_SPACE || layout[start.row()][start.column()] == INVALID_SPACE) {
            return false;
        } else if (layout[start.row()][start.column()] == EMPTY_SPACE) {
            return false;
        }
        
        layout[end.row()][end.column()] = layout[start.row()][start.column()];
        layout[start.row()][start.column()] = EMPTY_SPACE;
    }
    
    return true;
}

void BoardLayout::makeJump(Jump jump) {
    if (layout2[jump.endingCell.row][jump.endingCell.column].value == EMPTY_SPACE) {
        layout2[jump.endingCell.row][jump.endingCell.column] = jump.endingCell;
        Cell replacementCell = jump.startingCell;
        replacementCell.value = EMPTY_SPACE;
        layout2[replacementCell.row][replacementCell.column] = replacementCell;
    }
}

bool BoardLayout::isPaddockFull() {
    // TODO: There has to be a better way to do this...
    if (layout[0][2] == SHEEP_CHARACTER) {
        if (layout[0][3] == SHEEP_CHARACTER) {
            if (layout[0][4] == SHEEP_CHARACTER) {
                if (layout[1][2] == SHEEP_CHARACTER) {
                    if (layout[1][3] == SHEEP_CHARACTER) {
                        if (layout[1][4] == SHEEP_CHARACTER) {
                            if (layout[2][2] == SHEEP_CHARACTER) {
                                if (layout[2][3] == SHEEP_CHARACTER) {
                                    if (layout[2][4] == SHEEP_CHARACTER) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

int BoardLayout::sheepRemaining() {
    int count = 0;
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            if (layout[row][column] == SHEEP_CHARACTER) {
                count++;
            }
        }
    }
    
    return count;
}

std::vector<Coordinate> BoardLayout::getFoxCoordinates() {
    std::vector<Coordinate> coordinates;
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            if (layout[row][column] == FOX_CHARACTER) {
                coordinates.push_back(Coordinate(row, column));
            }
        }
    }
    
    return coordinates;
}

std::vector<Cell> BoardLayout::getFoxCells() {
    std::vector<Cell> cells;
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            if (layout2[row][column].value == FOX_CHARACTER) {
                cells.push_back(layout2[row][column]);
            }
        }
    }
    return cells;
}
