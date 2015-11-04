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
#include "Move.h"

const char INVALID_SPACE = ' ';
const char EMPTY_SPACE = '.';
const char FOX_CHARACTER = 'F';
const char SHEEP_CHARACTER = 'S';

class BoardLayout {
    
    char layout[7][7];
    
public:
    
    enum BoardValue : char {
        InvalidSpace = ' ',
        EmptySpace = '.',
        Fox = 'F',
        Sheep = 'S'
    };
    
    BoardLayout();
    BoardLayout(char layout[7][7]);
    BoardLayout(const BoardLayout& layout);
    
    char getValueAt(Coordinate coordinate);
    bool isValidCoordinate(Coordinate coordinate);
    
    bool applyMove(Move move);
    
    bool isPaddockFull();
    int sheepRemaining();
    
    std::vector<Coordinate> getFoxCoordinates();
};

#endif /* BoardLayout_h */
