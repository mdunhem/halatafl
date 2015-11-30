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

Move FoxPlayer::getMove(const Board &board, const std::string &message, const std::string &testMove) const {
    
    std::srand(time(NULL));
    
    std::vector<Cell> foxCells = board.getFoxCells();
    
    Fox foxOne(foxCells[0]);
    Fox foxTwo(foxCells[1]);
    
    foxOne = search(board, foxOne);
    foxTwo = search(board, foxTwo);
    
    Move move;
    
    if (foxOne.getMoves().size() || foxTwo.getMoves().size()) {
        Move *foxOneMove = foxOne.getMove();
        Move *foxTwoMove = foxTwo.getMove();
        if (foxOneMove == nullptr && foxTwoMove != nullptr) {
            move = *foxTwoMove;
        } else if (foxOneMove != nullptr && foxTwoMove == nullptr) {
            move = *foxOneMove;
        } else {
            if (*foxTwoMove < *foxOneMove) {
                move = *foxOneMove;
            } else if (*foxOneMove < *foxTwoMove) {
                move = *foxTwoMove;
            } else {
                move = std::rand() % 2 ? *foxOneMove : *foxTwoMove;
            }
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

Fox FoxPlayer::search(Board board, Fox fox) const {
    std::map<Board::Direction, Cell>surroundingValues = board.getSurroundingCells(fox.getCell());
    
    for (auto surroundingValue : surroundingValues) {
        Board::Direction direction = surroundingValue.first;
        Cell cell = surroundingValue.second;
        Cell jumpToCell = board.getCellInDirectionFromCellWithRadius(direction, cell);
        Cell foxCell = board.getCellInDirectionFromCellWithRadius(direction, cell, -1);
        foxCell.setValue(Cell::Value::fox);
        
        if (cell.isSheep()) {
            fox = searchForJumps(board, fox, direction, cell);
            fox.setCell(foxCell);
        } else if (cell.isEmpty()) {
            fox = searchForThreats(board, fox, cell);
        }
    }
    
    if (fox.getMoves().empty() && fox.getPossibleThreats().empty() && fox.getPossibleNonThreateningMoves().empty()) {
        fox.addPossibleNonThreateningMove(Move(fox.getCell(), fox.getCell()));
    }
    
    return fox;
}

Fox FoxPlayer::searchForJumps(Board board, Fox fox, Board::Direction direction, Cell cellToJump) const {
    Cell jumpToCell = board.getCellInDirectionFromCellWithRadius(direction, cellToJump);
    if (jumpToCell.isEmpty()) {
        jumpToCell.setValue(Cell::Value::fox);
        Jump jump(fox.getCell(), jumpToCell, cellToJump);
        fox.addJump(jump);
        board.makeJump(jump);
        fox.setCell(jumpToCell);
        std::map<Board::Direction, Cell>surroundingValues = board.getSurroundingCells(fox.getCell());
        for (auto surroundingValue : surroundingValues) {
            Board::Direction newDirection = surroundingValue.first;
            Cell cell = surroundingValue.second;
            if (cell.isSheep()) {
                fox = searchForJumps(board, fox, newDirection, cell);
            }
        }
    }
    return fox;
}

Fox FoxPlayer::searchForThreats(Board board, Fox fox, Cell cellToSearchFrom) const {
    std::map<Board::Direction, Cell>surroundingValues = board.getSurroundingCells(cellToSearchFrom);
    
    for (auto surroundingValue : surroundingValues) {
        Board::Direction direction = surroundingValue.first;
        Cell cell = surroundingValue.second;
        
        if (cell.isSheep()) {
            Cell jumpToCell = board.getCellInDirectionFromCellWithRadius(direction, cell);
            if (jumpToCell.isEmpty()) {
                fox.addPossibleThreat(Move(fox.getCell(), cellToSearchFrom));
            } else {
                fox.addPossibleNonThreateningMove(Move(fox.getCell(), cellToSearchFrom));
            }
        } else if (cell.isEmpty()) {
            fox.addPossibleNonThreateningMove(Move(fox.getCell(), cellToSearchFrom));
        }
    }
    
    return fox;
}
