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
    
    if (foxOne.getMove().jumps.size() > 0) {
        move = foxOne.getMove();
    } else if (foxTwo.getMove().jumps.size() > 0) {
        move = foxTwo.getMove();
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
                    }
                    break;
                }
                case down: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    }
                    break;
                }
                case left: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row, fox.getCell().column - 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row, fox.getCell().column - 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    }
                    break;
                }
                case right: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row, fox.getCell().column + 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row, fox.getCell().column + 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    }
                    break;
                }
                case upLeft: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row - 2, fox.getCell().column - 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row - 1, fox.getCell().column - 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    }
                    break;
                }
                case upRight: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row - 2, fox.getCell().column + 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row - 1, fox.getCell().column + 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    }
                    break;
                }
                case downLeft: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column - 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column - 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    }
                    break;
                }
                case downRight: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.getCell().row + 2, fox.getCell().column + 2);
                    Cell jumpedCell = boardLayout.getCellAtIndex(fox.getCell().row + 1, fox.getCell().column + 1);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        applyJump(boardLayout, fox, jumpToCell, jumpedCell);
                        search(boardLayout, fox);
                    }
                    break;
                }
                    
                default:
                    break;
            }
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



//Move FoxPlayer::getMove(BoardLayout boardLayout, std::string message) {
//
//    std::vector<Cell> foxCells = boardLayout.getFoxCells();
//    
//    foxOne.cell = foxCells[0];
//    foxOne.boardLayout = boardLayout;
//    foxTwo.cell = foxCells[1];
//    foxTwo.boardLayout = boardLayout;
//    
//    determinePossibleMove(boardLayout, foxOne);
//    determinePossibleMove(boardLayout, foxTwo);
//    
//    Move move;
//    Coordinate start(7, 'e');
//    Coordinate end(7, 'e');
//    Jump jump;
//    jump.start = start;
//    jump.end = end;
//    
//    move.jumps.push_back(jump);
//    return move;
//}
//
//void FoxPlayer::won() {
//    std::cout << "The foxes have won!" << std::endl;
//}
//
//void FoxPlayer::determinePossibleMove(BoardLayout &boardLayout, FoxPlayer::Fox &fox) {
//    fox.determineSurroundingValues(boardLayout);
//    
//    for (auto direction : fox.surroundingValues) {
//        std::cout << direction.first << " -> " << &direction.second.value << std::endl;
//        
//        if (direction.second.value == SHEEP_CHARACTER) {
//            switch (direction.first) {
//                case Fox::down: {
//                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.cell.row - 2, fox.cell.column);
//                    if (jumpToCell.value == EMPTY_SPACE) {
//                        Jump jump;
//                        jump.start = fox.cell;
//                        jump.end = jumpToCell;
//                        fox.move.jumps.push_back(jump);
//                        fox.cell = jumpToCell;
//                        fox.boardLayout.makeJump(jump);
//                    }
//                    break;
//                }
//                default: {
//                    break;
//                }
//            }
//        }
//    }
//    
//}
//
//void FoxPlayer::Fox::determineSurroundingValues(BoardLayout &boardLayout) {
//    surroundingValues[up] = boardLayout.getCellAtIndex(cell.row - 1, cell.column);
//    surroundingValues[down] = boardLayout.getCellAtIndex(cell.row + 1, cell.column);
//    surroundingValues[left] = boardLayout.getCellAtIndex(cell.row, cell.column - 1);
//    surroundingValues[right] = boardLayout.getCellAtIndex(cell.row, cell.column + 1);
//    surroundingValues[upLeft] = boardLayout.getCellAtIndex(cell.row - 1, cell.column - 1);
//    surroundingValues[upRight] = boardLayout.getCellAtIndex(cell.row - 1, cell.column + 1);
//    surroundingValues[downLeft] = boardLayout.getCellAtIndex(cell.row + 1, cell.column - 1);
//    surroundingValues[downRight] = boardLayout.getCellAtIndex(cell.row + 1, cell.column + 1);
//}
//
