//
//  Coordinate.cpp
//  halatafl
//
//  Created by Sven on 10/29/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Coordinate.h"

Coordinate::Coordinate() {
    _row = 0;
    _column = 'a';
}

Coordinate::Coordinate(int row, char column) {
    _row = convertRowCoordinate(row);
    _column = column;
}

Coordinate::Coordinate(int row, int column) {
    if (row < 0 || row > 6) {
        _row = -1;
    } else {
        _row = row;
    }
    _column = char(column + 97);
}

int Coordinate::row() {
    return _row;
}

int Coordinate::column() {
    int result = -1;
    
    switch(_column) {
        case 'a':
            result = 0;
            break;
        case 'b':
            result = 1;
            break;
        case 'c':
            result = 2;
            break;
        case 'd':
            result = 3;
            break;
        case 'e':
            result = 4;
            break;
        case 'f':
            result = 5;
            break;
        case 'g':
            result = 6;
            break;
        default:
            break;
    }
    
    return result;
}

int Coordinate::convertRowCoordinate(int row) {
    
    switch (row) {
        case 1:
            row = 6;
            break;
        case 2:
            row = 5;
            break;
        case 3:
            row = 4;
            break;
        case 4:
            row = 3;
            break;
        case 5:
            row = 2;
            break;
        case 6:
            row = 1;
            break;
        case 7:
            row = 0;
            break;
        default:
            row = -1;
            break;
    }
    
    return row;
}