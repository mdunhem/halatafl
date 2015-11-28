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

Move FoxPlayer::getMove(Board board, std::string message, bool isTest) {
    
    std::srand(time(NULL));
    
    std::vector<Cell> foxCells = board.getFoxCells();
    
    Fox foxOne(foxCells[0]);
    Fox foxTwo(foxCells[1]);
    
    determinePossibleMove(board, foxOne);
    determinePossibleMove(board, foxTwo);
    
    Move move;
    
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
                jumpToCell.setValue(Cell::Value::fox);
                Jump jump(foxCell, jumpToCell, cell);
                fox.addJump(jump);
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
    
    if (fox.getMoves().empty() && fox.getPossibleThreats().empty() && fox.getPossibleNonThreateningMoves().empty()) {
        fox.addJump(Jump(fox.getCell(), fox.getCell()));
    }
}
