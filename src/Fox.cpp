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

Fox::Fox(Board board, Cell cell) : board(board), cell(cell) {
    currentLocation = &cell;
}

Fox::Fox(const Fox &fox) :board(fox.board), cell(fox.cell), move(fox.move), possibleThreats(fox.possibleThreats) {
    currentLocation = &cell;
}

// Getters and setters
Cell Fox::getCell() const {
    return cell;
}
void Fox::setCell(Cell cell) {
    currentLocation = &cell;
    this->cell = cell;
}

Move Fox::getMove() {
    return move;
}
void Fox::setMove(Move move) {
    this->move = move;
}

std::vector<Move> Fox::getPossibleThreats() const {
    return possibleThreats;
}

std::vector<Move> Fox::getPossibleNonThreateningMoves() const {
    return possibleNonThreateningMoves;
}

void Fox::addPossibleThreat(Move threat) {
    possibleThreats.push_back(threat);
}

void Fox::addPossibleNonThreateningMove(Move move) {
    possibleNonThreateningMoves.push_back(move);
}

void Fox::determineSurroundingValues(Board &board) {
    surroundingValues[up] = board.getCellAtIndex(cell.row - 1, cell.column);
    surroundingValues[down] = board.getCellAtIndex(cell.row + 1, cell.column);
    surroundingValues[left] = board.getCellAtIndex(cell.row, cell.column - 1);
    surroundingValues[right] = board.getCellAtIndex(cell.row, cell.column + 1);
    surroundingValues[upLeft] = board.getCellAtIndex(cell.row - 1, cell.column - 1);
    surroundingValues[upRight] = board.getCellAtIndex(cell.row - 1, cell.column + 1);
    surroundingValues[downLeft] = board.getCellAtIndex(cell.row + 1, cell.column - 1);
    surroundingValues[downRight] = board.getCellAtIndex(cell.row + 1, cell.column + 1);
}


std::map<Direction, Cell> Fox::getSurroundingValuesWithRadius(Board &board, int radius) {
    std::map<Direction, Cell> values;
    values[up] = board.getCellAtIndex(cell.row - radius, cell.column);
    values[down] = board.getCellAtIndex(cell.row + radius, cell.column);
    values[left] = board.getCellAtIndex(cell.row, cell.column - radius);
    values[right] = board.getCellAtIndex(cell.row, cell.column + radius);
    values[upLeft] = board.getCellAtIndex(cell.row - radius, cell.column - radius);
    values[upRight] = board.getCellAtIndex(cell.row - radius, cell.column + radius);
    values[downLeft] = board.getCellAtIndex(cell.row + radius, cell.column - radius);
    values[downRight] = board.getCellAtIndex(cell.row + radius, cell.column + radius);
    
    return values;
}

void Fox::calculateMove() {
    std::map<Direction, Cell>surroundingValues = getSurroundingValuesWithRadius(board, 1);
    for (auto direction : surroundingValues) {
        if (direction.second.value == SHEEP_CHARACTER) {
            Cell jumpToCell = board.getCellInDirectionFromCell(direction.first, direction.second);
            if (jumpToCell.value == EMPTY_SPACE) {
                Jump jump(*currentLocation, jumpToCell);
                jump.jumpedCell = direction.second;
                move.jumps.push_back(jump);
            }
        } else {
            std::map<Direction, Cell>secondRowOfSurroundingValues = getSurroundingValuesWithRadius(board, 2);
            for (auto secondDirection : secondRowOfSurroundingValues) {
                if (secondDirection.second.value == SHEEP_CHARACTER) {
                    Cell jumpToCell = board.getCellInDirectionFromCell(secondDirection.first, secondDirection.second);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        Move jump(*currentLocation, secondDirection.second);
                        possibleThreats.push_back(jump);
                    }
                }
            }
        }
    }
}

void Fox::findPossibleJump(Board &board) {
    std::map<Direction, Cell>surroundingValues = getSurroundingValuesWithRadius(board, 1);
    for (auto direction : surroundingValues) {
        if (direction.second.value == SHEEP_CHARACTER) {
            switch (direction.first) {
                case down: {
                    Cell jumpToCell = board.getCellAtIndex(currentLocation->row + 2, currentLocation->column);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        Jump jump(*currentLocation, jumpToCell);
                        jump.jumpedCell = board.getCellAtIndex(currentLocation->row + 1, currentLocation->column);
                        move.jumps.push_back(jump);
                        currentLocation = &jumpToCell;
//                        cell = jumpToCell;
//                        cell.value = FOX_CHARACTER;
                        board.makeJump(jump);
                        findPossibleJump(board);
                    }
                    break;
                }
                case left: {
                    Cell jumpToCell = board.getCellAtIndex(currentLocation->row, currentLocation->column - 2);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        Jump jump(*currentLocation, jumpToCell);
                        jump.jumpedCell = board.getCellAtIndex(currentLocation->row, currentLocation->column - 1);
                        move.jumps.push_back(jump);
                        currentLocation = &jumpToCell;
//                        cell = jumpToCell;
//                        cell.value = FOX_CHARACTER;
                        board.makeJump(jump);
                        findPossibleJump(board);
                    }
                    break;
                }
                    
                default:
                    break;
            }
        }
    }
}

void Fox::addJump(Jump jump) {
    move.jumps.push_back(jump);
}

