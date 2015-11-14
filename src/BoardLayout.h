//
//  BoardLayout.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef BoardLayout_h
#define BoardLayout_h

#include "Coordinate.h"
#include "Cell.h"
#include "Move.h"

const char INVALID_SPACE = ' ';
const char EMPTY_SPACE = '.';
const char FOX_CHARACTER = 'F';
const char SHEEP_CHARACTER = 'S';

struct BoardValue {
    const char InvalidSpace = ' ';
    const char EmptySpace = '.';
    const char Fox = 'F';
    const char Sheep = 'S';
};

class BoardLayout {
    
    char layout[7][7];
    
    std::vector<std::vector<Cell> > layout2;
    
public:
    
//    enum BoardValue : char {
//        InvalidSpace = ' ',
//        EmptySpace = '.',
//        Fox = 'F',
//        Sheep = 'S'
//    };
    
    BoardLayout();
    BoardLayout(char layout[7][7]);
    BoardLayout(const BoardLayout& layout);
    
    char getValueAt(Coordinate coordinate);
    Cell getCellAtIndex(int x, int y);
    std::vector<Cell> cellsForRow(int row);
    char* operator[](int index);
    
    bool isValidCoordinate(Coordinate coordinate);
    
    bool applyMove(Move move);
    void makeJump(Jump jump);
    
    bool isPaddockFull();
    int sheepRemaining();
    
    std::vector<Coordinate> getFoxCoordinates();
    std::vector<Cell> getFoxCells();
};

#endif /* BoardLayout_h */
