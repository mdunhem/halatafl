//
//  FoxPlayer.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>

#include "FoxPlayer.h"


Move FoxPlayer::getMove(BoardLayout boardLayout, std::string message) {
    
    std::vector<Cell> foxCells = boardLayout.getFoxCells();
    
    foxOne.cell = foxCells[0];
    foxOne.boardLayout = boardLayout;
    foxTwo.cell = foxCells[1];
    foxTwo.boardLayout = boardLayout;
    
    determinePossibleMove(boardLayout, foxOne);
    determinePossibleMove(boardLayout, foxTwo);
    
    Move move;
    Coordinate start(7, 'e');
    Coordinate end(7, 'e');
    Jump jump;
    jump.start = start;
    jump.end = end;
    
    move.jumps.push_back(jump);
    return move;
}

void FoxPlayer::won() {
    std::cout << "The foxes have won!" << std::endl;
}

void FoxPlayer::determinePossibleMove(BoardLayout &boardLayout, FoxPlayer::Fox &fox) {
    fox.determineSurroundingValues(boardLayout);
    
    for (auto direction : fox.surroundingValues) {
        std::cout << direction.first << " -> " << &direction.second.value << std::endl;
        
        if (direction.second.value == SHEEP_CHARACTER) {
            switch (direction.first) {
                case Fox::down: {
                    Cell jumpToCell = boardLayout.getCellAtIndex(fox.cell.row - 2, fox.cell.column);
                    if (jumpToCell.value == EMPTY_SPACE) {
                        Jump jump;
                        jump.startingCell = fox.cell;
                        jump.endingCell = jumpToCell;
                        fox.move.jumps.push_back(jump);
                        fox.cell = jumpToCell;
                        fox.boardLayout.makeJump(jump);
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }
    
}

void FoxPlayer::Fox::determineSurroundingValues(BoardLayout &boardLayout) {
    surroundingValues[up] = boardLayout.getCellAtIndex(cell.row - 1, cell.column);
    surroundingValues[down] = boardLayout.getCellAtIndex(cell.row + 1, cell.column);
    surroundingValues[left] = boardLayout.getCellAtIndex(cell.row, cell.column - 1);
    surroundingValues[right] = boardLayout.getCellAtIndex(cell.row, cell.column + 1);
    surroundingValues[upLeft] = boardLayout.getCellAtIndex(cell.row - 1, cell.column - 1);
    surroundingValues[upRight] = boardLayout.getCellAtIndex(cell.row - 1, cell.column + 1);
    surroundingValues[downLeft] = boardLayout.getCellAtIndex(cell.row + 1, cell.column - 1);
    surroundingValues[downRight] = boardLayout.getCellAtIndex(cell.row + 1, cell.column + 1);
}

