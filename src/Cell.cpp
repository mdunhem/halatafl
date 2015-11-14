//
//  Cell.cpp
//  halatafl
//
//  Created by Mike on 11/13/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Cell.h"

Cell::Cell() : row(0), column(0), value(' ') {}

Cell::Cell(int row, int column, char value) : row(row), column(column), value(value) {}

//Cell::Cell(const Cell& cell) : x(cell.x), y(cell.y), value(cell.value) {}
//
//Cell& Cell::operator=(const Cell &cell) {
//    value = cell.value;
//    return *this;
//}

char Cell::getColumnCharacter() {
    char value;
    switch (column) {
        case 0:
            value = 'a';
            break;
        case 1:
            value = 'b';
            break;
        case 2:
            value = 'c';
            break;
        case 3:
            value = 'd';
            break;
        case 4:
            value = 'e';
            break;
        case 5:
            value = 'f';
            break;
        case 6:
            value = 'g';
            break;
            
        default:
            break;
    }
    
    return value;
}