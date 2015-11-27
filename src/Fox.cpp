//
//  Fox.cpp
//  halatafl
//
//  Created by Mike on 11/14/15.
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
    if (moves.size()) {
        Move *moveToBeUsed = &moves.front();
        for (std::vector<Move>::iterator iterator = moves.begin(); iterator != moves.end(); iterator++) {
            if (Move(*iterator).jumps.size() > moveToBeUsed->jumps.size()) {
                *moveToBeUsed = Move(*iterator);
            }
        }
        return *moveToBeUsed;
    }
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
    surroundingValues[Board::Direction::up] = board.getCellAtIndex(cell.row - 1, cell.column);
    surroundingValues[Board::Direction::down] = board.getCellAtIndex(cell.row + 1, cell.column);
    surroundingValues[Board::Direction::left] = board.getCellAtIndex(cell.row, cell.column - 1);
    surroundingValues[Board::Direction::right] = board.getCellAtIndex(cell.row, cell.column + 1);
    surroundingValues[Board::Direction::upLeft] = board.getCellAtIndex(cell.row - 1, cell.column - 1);
    surroundingValues[Board::Direction::upRight] = board.getCellAtIndex(cell.row - 1, cell.column + 1);
    surroundingValues[Board::Direction::downLeft] = board.getCellAtIndex(cell.row + 1, cell.column - 1);
    surroundingValues[Board::Direction::downRight] = board.getCellAtIndex(cell.row + 1, cell.column + 1);
}


std::map<Board::Direction, Cell> Fox::getSurroundingValuesWithRadius(Board &board, int radius) {
    std::map<Board::Direction, Cell> values;
    values[Board::Direction::up] = board.getCellAtIndex(cell.row - radius, cell.column);
    values[Board::Direction::down] = board.getCellAtIndex(cell.row + radius, cell.column);
    values[Board::Direction::left] = board.getCellAtIndex(cell.row, cell.column - radius);
    values[Board::Direction::right] = board.getCellAtIndex(cell.row, cell.column + radius);
    values[Board::Direction::upLeft] = board.getCellAtIndex(cell.row - radius, cell.column - radius);
    values[Board::Direction::upRight] = board.getCellAtIndex(cell.row - radius, cell.column + radius);
    values[Board::Direction::downLeft] = board.getCellAtIndex(cell.row + radius, cell.column - radius);
    values[Board::Direction::downRight] = board.getCellAtIndex(cell.row + radius, cell.column + radius);
    
    return values;
}

//void Fox::calculateMove() {
//    std::map<Board::Direction, Cell>surroundingValues = getSurroundingValuesWithRadius(board, 1);
//    for (auto direction : surroundingValues) {
//        if (direction.second.value == SHEEP_CHARACTER) {
//            Cell jumpToCell = board.getCellInDirectionFromCell(direction.first, direction.second);
//            if (jumpToCell.value == EMPTY_SPACE) {
//                Jump jump(*currentLocation, jumpToCell);
//                jump.jumpedCell = direction.second;
//                move.jumps.push_back(jump);
//            }
//        } else {
//            std::map<Board::Direction, Cell>secondRowOfSurroundingValues = getSurroundingValuesWithRadius(board, 2);
//            for (auto secondDirection : secondRowOfSurroundingValues) {
//                if (secondDirection.second.value == SHEEP_CHARACTER) {
//                    Cell jumpToCell = board.getCellInDirectionFromCell(secondDirection.first, secondDirection.second);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        Move jump(*currentLocation, secondDirection.second);
//                        possibleThreats.push_back(jump);
//                    }
//                }
//            }
//        }
//    }
//}

void Fox::findPossibleJump(Board &board) {
    std::map<Board::Direction, Cell>surroundingValues = getSurroundingValuesWithRadius(board, 1);
    for (auto direction : surroundingValues) {
        if (direction.second.value == SHEEP_CHARACTER) {
            switch (direction.first) {
                case Board::Direction::down: {
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
                case Board::Direction::left: {
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
    if (moves.size()) {
        if (moves.back().jumps.back().end == jump.start) {
            moves.back().jumps.push_back(jump);
        } else {
            Move newMove = moves.back();
            newMove.jumps.pop_back();
            newMove.jumps.push_back(jump);
            moves.push_back(newMove);
        }
    } else {
        moves.push_back(Move(jump));
    }
//    move.jumps.push_back(jump);
}

void Fox::addJumpToMove(Jump jump, Move *move) {
    if (move != nullptr) {
        move->jumps.push_back(jump);
    } else {
        moves.push_back(Move(jump));
    }
}

