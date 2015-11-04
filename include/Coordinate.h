//
//  Coordinate.hpp
//  halatafl
//
//  Created by Sven on 10/29/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Coordinate_h
#define Coordinate_h

#include <stdio.h>

struct Coordinate {
    Coordinate();
    Coordinate(int row, char column);
    Coordinate(int row, int column);
    
    int row();
    int column();
    
private:
    int convertRowCoordinate(int row);
    int _row;
    char _column;
};

#endif /* Coordinate_h */
