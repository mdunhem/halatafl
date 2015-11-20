//
//  BoardLayout.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef BoardLayout_h
#define BoardLayout_h

#include "Cell.h"
#include "Move.h"

const char INVALID_SPACE = ' ';
const char EMPTY_SPACE = '.';
const char FOX_CHARACTER = 'F';
const char SHEEP_CHARACTER = 'S';

//struct BoardValue {
//    const char InvalidSpace = ' ';
//    const char EmptySpace = '.';
//    const char Fox = 'F';
//    const char Sheep = 'S';
//};

enum Direction {
    up, down, left, right, upLeft, upRight, downLeft, downRight
};

class BoardLayout {
    
    std::vector<std::vector<Cell> > layout;
    
public:
    
    BoardLayout();
    BoardLayout(char layout[7][7]);
    BoardLayout(const BoardLayout& layout);
    
    Cell getCellAtIndex(int x, int y);
    Cell getCellInDirectionFromCell(Direction direction, Cell &cell);
    std::vector<Cell> cellsForRow(int row);
    
    bool applyMove(Move move);
    void makeJump(Jump jump);
    
    bool isValidMove(Move move);
    
    bool isPaddockFull();
    int sheepRemaining();
    
    std::vector<Cell> getFoxCells();
};

#endif /* BoardLayout_h */
