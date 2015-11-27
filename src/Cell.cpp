//
//  Cell.cpp
//  halatafl
//
//  Created by Mike on 11/13/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Cell.h"

#include "Board.h"

const char Cell::printableValues[] = { ' ', '.', 'S', 'F' };
const char Cell::printableColumns[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
const int Cell::printableRows[] = { 7, 6, 5, 4, 3, 2, 1 };

Cell::Cell() : row(0), column(0), value(INVALID_SPACE), cellValue(invalid) {}

Cell::Cell(int row, int column, char value) : row(row), column(column), value(value) {
    for (int i = 0; i < 4; i++) {
        if (value == printableValues[i]) {
            cellValue = static_cast<Value>(i);
        }
    }
}

Cell::Cell(int row, char column, char value) : row(row), value(value) {
    switch(column) {
        case 'a':
            this->column = 0;
            break;
        case 'b':
            this->column = 1;
            break;
        case 'c':
            this->column = 2;
            break;
        case 'd':
            this->column = 3;
            break;
        case 'e':
            this->column = 4;
            break;
        case 'f':
            this->column = 5;
            break;
        case 'g':
            this->column = 6;
            break;
        default:
            this->column = 0;
            break;
    }
}

Cell::Cell(int row, int column, Value value) : row(row), column(column), cellValue(value) {
    
}

bool Cell::isSheep() const {
    return cellValue == sheep;
}

bool Cell::isFox() const {
    return cellValue == fox;
}

bool Cell::isEmpty() const {
    return cellValue == empty;
}

bool Cell::isInvalid() const {
    return cellValue == invalid;
}

//Cell::Cell(const Cell& cell) : x(cell.x), y(cell.y), value(cell.value) {}
//
//Cell& Cell::operator=(const Cell &cell) {
//    value = cell.value;
//    return *this;
//}

char Cell::getColumnCharacter() const {
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

int Cell::printableRow() const {
    int printableRow = 0;
    switch (row) {
        case 0: {
            printableRow = 7;
            break;
        }
        case 1: {
            printableRow = 6;
            break;
        }
        case 2: {
            printableRow = 5;
            break;
        }
        case 3: {
            printableRow = 4;
            break;
        }
        case 4: {
            printableRow = 3;
            break;
        }
        case 5: {
            printableRow = 2;
            break;
        }
        case 6: {
            printableRow = 1;
            break;
        }
            
        default:
            break;
    }
    return printableRow;
}

void Cell::print(std::ostream &output) const {
    output << printableColumns[column] << printableRows[row];
}

bool Cell::operator==(const Cell &cell) const {
    if (cell.row == row && cell.column == column && cell.value == value) {
        return true;
    }
    return false;
}

bool Cell::operator!=(const Cell &cell) const {
    if (cell.row != row || cell.column != column || cell.value != value) {
        return true;
    }
    return false;
}

