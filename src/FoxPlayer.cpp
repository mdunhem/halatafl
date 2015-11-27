//
//  FoxPlayer.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "FoxPlayer.h"

Move FoxPlayer::getMove(Board board, std::string message, bool isTest) {
    
    std::srand(time(NULL));
    
    std::vector<Cell> foxCells = board.getFoxCells();
    
    Fox foxOne(board, foxCells[0]);
    Fox foxTwo(board, foxCells[1]);
    
    determinePossibleMove(board, foxOne);
    determinePossibleMove(board, foxTwo);
    
    Move move;
    
    // TODO: Need to randomize the last part of this if block
    if (foxOne.getMove().jumps.size() > foxTwo.getMove().jumps.size()) {
        move = foxOne.getMove();
    } else if (foxOne.getMove().jumps.size() < foxTwo.getMove().jumps.size()) {
        move = foxTwo.getMove();
    } else if (foxOne.getPossibleThreats().size() > 0 || foxTwo.getPossibleThreats().size() > 0) {
        if (foxOne.getPossibleThreats().size() > foxTwo.getPossibleThreats().size()) {
            move = foxOne.getPossibleThreats()[std::rand() % foxOne.getPossibleThreats().size()];
        } else {
            move = foxTwo.getPossibleThreats()[std::rand() % foxTwo.getPossibleThreats().size()];
        }
    } else if (foxOne.getPossibleNonThreateningMoves().size() > 0 || foxTwo.getPossibleNonThreateningMoves().size() > 0) {
        if (foxOne.getPossibleNonThreateningMoves().size() > foxTwo.getPossibleNonThreateningMoves().size()) {
            move = foxOne.getPossibleNonThreateningMoves()[std::rand() % foxOne.getPossibleNonThreateningMoves().size()];
        } else {
            move = foxTwo.getPossibleNonThreateningMoves()[std::rand() % foxTwo.getPossibleNonThreateningMoves().size()];
        }
    } else {
        move = std::rand() % 2 ? foxOne.getMove() : foxTwo.getMove();
//        move = Move(foxOne.getCell(), foxOne.getCell());
    }
    
    std::cout << "The foxes move: " << move << std::endl;
    
    return move;
}

void FoxPlayer::won() {
    std::cout << "The foxes have won!" << std::endl;
}

void FoxPlayer::determinePossibleMove(Board board, Fox &fox) {
    search(board, fox);
}

void FoxPlayer::search(Board &board, Fox &fox) {
    std::map<Board::Direction, Cell>surroundingValues = board.getSurroundingCells(fox.getCell());
    
    for (auto surroundingValue : surroundingValues) {
        Board::Direction direction = surroundingValue.first;
        Cell cell = surroundingValue.second;
        Cell jumpToCell = board.getCellInDirectionFromCellWithRadius(direction, cell);
        Cell foxCell = board.getCellInDirectionFromCellWithRadius(direction, cell, -1);
        
        if (cell.isSheep()) {
            if (jumpToCell.isEmpty()) {
                Jump jump(foxCell, jumpToCell);
                jump.jumpedCell = cell;
                fox.addJump(jump);
                jumpToCell.cellValue = Cell::Value::fox;
                board.makeJump(jump);
                fox.setCell(jumpToCell);
                // Recursively call this function again to search for additional jumps
                search(board, fox);
            } else {
                fox.addPossibleNonThreateningMove(Move(fox.getCell(), fox.getCell()));
            }
        } else {
            if (cell.isEmpty() && jumpToCell.isSheep()) {
                Cell threatenToJumpToCell = board.getCellInDirectionFromCellWithRadius(direction, jumpToCell);
                if (threatenToJumpToCell.isEmpty()) {
                    fox.addPossibleThreat(Move(foxCell, cell));
                } else {
                    fox.addPossibleNonThreateningMove(Move(foxCell, cell));
                }
            } else if (cell.isEmpty()) {
                fox.addPossibleNonThreateningMove(Move(foxCell, cell));
            }
        }
    }
    
    if (fox.moves.empty() && fox.getPossibleThreats().empty() && fox.getPossibleNonThreateningMoves().empty()) {
        fox.addJump(Jump(fox.cell, fox.cell));
    }
}

//    std::map<Board::Direction, Cell>surroundingValues = fox.getSurroundingValuesWithRadius(board, 1);
//    for (auto direction : surroundingValues) {
//        if (direction.second.value == SHEEP_CHARACTER) {
//            switch (direction.first) {
//                case Board::Direction::up: {
//                    Cell jumpToCell = board.getCellAtIndex(fox.getCell().row - 2, fox.getCell().column);
//                    Cell jumpedCell = board.getCellAtIndex(fox.getCell().row - 1, fox.getCell().column);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        applyJump(board, fox, jumpToCell, jumpedCell);
//                        search(board, fox);
//                    } else {
//                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
//                    }
//                    break;
//                }
//                case Board::Direction::down: {
//                    Cell jumpToCell = board.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column);
//                    Cell jumpedCell = board.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        applyJump(board, fox, jumpToCell, jumpedCell);
//                        search(board, fox);
//                    } else {
//                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
//                    }
//                    break;
//                }
//                case Board::Direction::left: {
//                    Cell jumpToCell = board.getCellAtIndex(fox.getCell().row, fox.getCell().column - 2);
//                    Cell jumpedCell = board.getCellAtIndex(fox.getCell().row, fox.getCell().column - 1);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        applyJump(board, fox, jumpToCell, jumpedCell);
//                        search(board, fox);
//                    } else {
//                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
//                    }
//                    break;
//                }
//                case Board::Direction::right: {
//                    Cell jumpToCell = board.getCellAtIndex(fox.getCell().row, fox.getCell().column + 2);
//                    Cell jumpedCell = board.getCellAtIndex(fox.getCell().row, fox.getCell().column + 1);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        applyJump(board, fox, jumpToCell, jumpedCell);
//                        search(board, fox);
//                    } else {
//                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
//                    }
//                    break;
//                }
//                case Board::Direction::upLeft: {
//                    Cell jumpToCell = board.getCellAtIndex(fox.getCell().row - 2, fox.getCell().column - 2);
//                    Cell jumpedCell = board.getCellAtIndex(fox.getCell().row - 1, fox.getCell().column - 1);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        applyJump(board, fox, jumpToCell, jumpedCell);
//                        search(board, fox);
//                    } else {
//                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
//                    }
//                    break;
//                }
//                case Board::Direction::upRight: {
//                    Cell jumpToCell = board.getCellAtIndex(fox.getCell().row - 2, fox.getCell().column + 2);
//                    Cell jumpedCell = board.getCellAtIndex(fox.getCell().row - 1, fox.getCell().column + 1);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        applyJump(board, fox, jumpToCell, jumpedCell);
//                        search(board, fox);
//                    } else {
//                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
//                    }
//                    break;
//                }
//                case Board::Direction::downLeft: {
//                    Cell jumpToCell = board.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column - 2);
//                    Cell jumpedCell = board.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column - 1);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        applyJump(board, fox, jumpToCell, jumpedCell);
//                        search(board, fox);
//                    } else {
//                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
//                    }
//                    break;
//                }
//                case Board::Direction::downRight: {
//                    Cell jumpToCell = board.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column + 2);
//                    Cell jumpedCell = board.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column + 1);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        applyJump(board, fox, jumpToCell, jumpedCell);
//                        search(board, fox);
//                    } else {
//                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
//                    }
//                    break;
//                }
//
//                default:
//                    break;
//            }
//        } else if (direction.second.value == EMPTY_SPACE) {
//            fox.addPossibleNonThreateningMove(Move(fox.getCell(), direction.second));
//        }
//    }