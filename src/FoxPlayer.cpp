//
//  FoxPlayer.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>

#include "FoxPlayer.h"

Move FoxPlayer::getMove(BoardLayout boardLayout, std::string message, bool isTest) {
    
    std::vector<Cell> foxCells = boardLayout.getFoxCells();
    
    Fox fox1(boardLayout, foxCells[0]);
    Fox fox2(boardLayout, foxCells[1]);
    
    foxOne.setCell(foxCells[0]);
    foxTwo.setCell(foxCells[1]);
    
    determinePossibleMove(boardLayout, foxOne);
    determinePossibleMove(boardLayout, foxTwo);
    
    Move move;
    
    // TODO: Need to randomize the last part of this if block
    if (foxOne.getMove().jumps.size() > foxTwo.getMove().jumps.size()) {
        move = foxOne.getMove();
    } else if (foxTwo.getMove().jumps.size() < foxTwo.getMove().jumps.size()) {
        move = foxTwo.getMove();
    } else if (foxOne.getPossibleThreats().size() > 0 || foxTwo.getPossibleThreats().size() > 0) {
        if (foxOne.getPossibleThreats().size() > foxTwo.getPossibleThreats().size()) {
            move = foxOne.getPossibleThreats()[0];
        } else {
            move = foxTwo.getPossibleThreats()[0];
        }
    } else if (foxOne.getPossibleNonThreateningMoves().size() > 0 || foxTwo.getPossibleNonThreateningMoves().size() > 0) {
        if (foxOne.getPossibleNonThreateningMoves().size() > foxTwo.getPossibleNonThreateningMoves().size()) {
            move = foxOne.getPossibleNonThreateningMoves()[0];
        } else {
            move = foxTwo.getPossibleNonThreateningMoves()[0];
        }
    } else {
        move = Move(foxOne.getCell(), foxOne.getCell());
    }
    
    std::cout << "The foxes move: " << move << std::endl;
    
    return move;
}

void FoxPlayer::won() {
    std::cout << "The foxes have won!" << std::endl;
}

void FoxPlayer::determinePossibleMove(BoardLayout boardLayout, Fox &fox) {
    search(boardLayout, fox);
}

void FoxPlayer::search(BoardLayout &boardLayout, Fox &fox) {
    std::map<Direction, Cell>surroundingValues = fox.getSurroundingValuesWithRadius(boardLayout, 1);
    for (auto direction : surroundingValues) {
        if (direction.second.value == SHEEP_CHARACTER) {
            switch (direction.first) {
                case up: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row - 2, fox.getCell().column);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row - 1, fox.getCell().column);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    } else {
                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
                    }
                    break;
                }
                case down: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    } else {
                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
                    }
                    break;
                }
                case left: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row, fox.getCell().column - 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row, fox.getCell().column - 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    } else {
                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
                    }
                    break;
                }
                case right: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row, fox.getCell().column + 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row, fox.getCell().column + 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    } else {
                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
                    }
                    break;
                }
                case upLeft: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row - 2, fox.getCell().column - 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row - 1, fox.getCell().column - 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    } else {
                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
                    }
                    break;
                }
                case upRight: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row - 2, fox.getCell().column + 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row - 1, fox.getCell().column + 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    } else {
                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
                    }
                    break;
                }
                case downLeft: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column - 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column - 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    } else {
                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
                    }
                    break;
                }
                case downRight: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column + 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column + 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    } else {
                        fox.addPossibleThreat(Move(fox.getCell(), direction.second));
                    }
                    break;
                }
                    
                default:
                    break;
            }
        } else if (direction.second.value == EMPTY_SPACE) {
            fox.addPossibleNonThreateningMove(Move(fox.getCell(), direction.second));
        }
    }
}

void FoxPlayer::applyJump(BoardLayout &boardLayout, Fox &fox, Cell &jumpToCell, Cell &jumpedCell) {
    Jump jump(fox.getCell(), jumpToCell);
    jump.jumpedCell = jumpedCell;
    fox.addJump(jump);
    jumpToCell.value = FOX_CHARACTER;
    boardLayout.makeJump(jump);
    fox.setCell(jumpToCell);
}

