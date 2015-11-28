//
//  FoxPlayer.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>

#include "FoxPlayer.h"
#include "Jump.h"

Move FoxPlayer::getMove(const Board &board, const std::string &message, const bool &isTest) const {
    
    std::srand(time(NULL));
    
    std::vector<Cell> foxCells = board.getFoxCells();
    
    Fox foxOne(foxCells[0]);
    Fox foxTwo(foxCells[1]);
    
    determinePossibleMove(board, foxOne);
    determinePossibleMove(board, foxTwo);
    
    Move move;
    
    if (foxOne.getMoves().size() || foxTwo.getMoves().size()) {
        if (foxTwo < foxOne) {
            move = foxOne.getMove();
        } else if (foxOne < foxTwo) {
            move = foxTwo.getMove();
        } else {
            move = std::rand() % 2 ? foxOne.getMove() : foxTwo.getMove();
        }
    } else if (foxOne.getPossibleThreats().size() || foxTwo.getPossibleThreats().size()) {
        if (foxTwo.getPossibleThreats().size() < foxOne.getPossibleThreats().size()) {
            move = foxOne.getPossibleThreats()[std::rand() % foxOne.getPossibleThreats().size()];
        } else if (foxOne.getPossibleThreats().size() < foxTwo.getPossibleThreats().size()) {
            move = foxTwo.getPossibleThreats()[std::rand() % foxTwo.getPossibleThreats().size()];
        } else {
            if (std::rand() % 2) {
                move = foxOne.getPossibleThreats()[std::rand() % foxOne.getPossibleThreats().size()];
            } else {
                move = foxTwo.getPossibleThreats()[std::rand() % foxTwo.getPossibleThreats().size()];
            }
        }
    } else {
        if (std::rand() % 2) {
            move = foxOne.getPossibleNonThreateningMoves()[std::rand() % foxOne.getPossibleNonThreateningMoves().size()];
        } else {
            move = foxTwo.getPossibleNonThreateningMoves()[std::rand() % foxTwo.getPossibleNonThreateningMoves().size()];
        }
    }
    
    std::cout << "The foxes move: " << move << std::endl;
    
    return move;
}

void FoxPlayer::won() const {
    std::cout << "The foxes have won!" << std::endl;
}

void FoxPlayer::determinePossibleMove(Board board, Fox &fox) const {
    search(board, fox);
}

void FoxPlayer::search(Board &board, Fox &fox, bool sheepHasBeenFound) const {
    std::map<Board::Direction, Cell>surroundingValues = board.getSurroundingCells(fox.getCell());
    
    for (auto surroundingValue : surroundingValues) {
        Board::Direction direction = surroundingValue.first;
        Cell cell = surroundingValue.second;
        Cell jumpToCell = board.getCellInDirectionFromCellWithRadius(direction, cell);
        Cell foxCell = board.getCellInDirectionFromCellWithRadius(direction, cell, -1);
        
        if (cell.isSheep()) {
            if (jumpToCell.isEmpty()) {
                jumpToCell.setValue(Cell::Value::fox);
                Jump jump(foxCell, jumpToCell, cell);
                fox.addJump(jump);
                board.makeJump(jump);
                fox.setCell(jumpToCell);
                // Recursively call this function again to search for additional jumps
                search(board, fox, true);
            } else {
                fox.addPossibleNonThreateningMove(Move(fox.getCell(), fox.getCell()));
            }
        } else if (!sheepHasBeenFound) {
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
    
    if (fox.getMoves().empty() && fox.getPossibleThreats().empty() && fox.getPossibleNonThreateningMoves().empty()) {
        fox.addPossibleNonThreateningMove(Move(fox.getCell(), fox.getCell()));
    }
}
