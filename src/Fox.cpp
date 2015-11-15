//
//  Fox.cpp
//  halatafl
//
//  Created by Sven on 11/14/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Fox.h"

// Getters and setters
Cell Fox::getCell() {
    return cell;
}
void Fox::setCell(Cell cell) {
    this->cell = cell;
}

Move Fox::getMove() {
    return move;
}
void Fox::setMove(Move move) {
    this->move = move;
}

BoardLayout Fox::getBoardLayout() {
    return boardLayout;
}
void Fox::setBoardLayout(BoardLayout boardLayout) {
    this->boardLayout = boardLayout;
}

void Fox::determineSurroundingValues(BoardLayout &boardLayout) {
    surroundingValues[up] = boardLayout.getCellAtIndex(cell.row - 1, cell.column);
    surroundingValues[down] = boardLayout.getCellAtIndex(cell.row + 1, cell.column);
    surroundingValues[left] = boardLayout.getCellAtIndex(cell.row, cell.column - 1);
    surroundingValues[right] = boardLayout.getCellAtIndex(cell.row, cell.column + 1);
    surroundingValues[upLeft] = boardLayout.getCellAtIndex(cell.row - 1, cell.column - 1);
    surroundingValues[upRight] = boardLayout.getCellAtIndex(cell.row - 1, cell.column + 1);
    surroundingValues[downLeft] = boardLayout.getCellAtIndex(cell.row + 1, cell.column - 1);
    surroundingValues[downRight] = boardLayout.getCellAtIndex(cell.row + 1, cell.column + 1);
}


std::map<Direction, Cell> Fox::getSurroundingValuesWithRadius(BoardLayout &boardLayout, int radius) {
    std::map<Direction, Cell> values;
    values[up] = boardLayout.getCellAtIndex(cell.row - 1, cell.column);
    values[down] = boardLayout.getCellAtIndex(cell.row + 1, cell.column);
    values[left] = boardLayout.getCellAtIndex(cell.row, cell.column - 1);
    values[right] = boardLayout.getCellAtIndex(cell.row, cell.column + 1);
    values[upLeft] = boardLayout.getCellAtIndex(cell.row - 1, cell.column - 1);
    values[upRight] = boardLayout.getCellAtIndex(cell.row - 1, cell.column + 1);
    values[downLeft] = boardLayout.getCellAtIndex(cell.row + 1, cell.column - 1);
    values[downRight] = boardLayout.getCellAtIndex(cell.row + 1, cell.column + 1);
    
    return values;
}

void Fox::findPossibleJump() {
    
}
