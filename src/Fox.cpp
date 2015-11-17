//
//  Fox.cpp
//  halatafl
//
//  Created by Sven on 11/14/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Fox.h"

// Constructors
Fox::Fox() {}

Fox::Fox(/*BoardLayout boardLayout,*/ Cell cell) : /* boardLayout(boardLayout), */ cell(cell) {
    
}

Fox::Fox(const Fox &fox) : /*boardLayout(fox.boardLayout),*/ cell(fox.cell), move(fox.move), possibleThreats(fox.possibleThreats) {
    
}

// Getters and setters
Cell Fox::getCell() const {
    return cell;
}
void Fox::setCell(Cell cell) {
    this->cell = cell;
}

Move Fox::getMove() const {
    return move;
}
void Fox::setMove(Move move) {
    this->move = move;
}

//BoardLayout Fox::getBoardLayout() const {
//    return boardLayout;
//}
//void Fox::setBoardLayout(BoardLayout boardLayout) {
//    this->boardLayout = boardLayout;
//}

std::vector<Move> Fox::getPossibleThreats() const {
    return possibleThreats;
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

void Fox::findPossibleJump(BoardLayout &boardLayout) {
    std::map<Direction, Cell>surroundingValues = getSurroundingValuesWithRadius(boardLayout, 1);
    for (auto direction : surroundingValues) {
        if (direction.second.value == SHEEP_CHARACTER) {
            switch (direction.first) {
                case down: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(cell.row + 2, cell.column);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        Jump jump(cell, jumpToCell);
                        jump.jumpedCell = boardLayout.getCellAtIndex(cell.row + 1, cell.column);
                        move.jumps.push_back(jump);
                        cell = jumpToCell;
                        cell.value = FOX_CHARACTER;
                        boardLayout.makeJump(jump);
                        findPossibleJump(boardLayout);
                    }
                    break;
                }
                case left: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(cell.row, cell.column - 2);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        Jump jump(cell, jumpToCell);
                        jump.jumpedCell = boardLayout.getCellAtIndex(cell.row, cell.column - 1);
                        move.jumps.push_back(jump);
                        cell = jumpToCell;
                        cell.value = FOX_CHARACTER;
                        boardLayout.makeJump(jump);
                        findPossibleJump(boardLayout);
                    }
                    break;
                }
                    
                default:
                    break;
            }
        }
    }
}



