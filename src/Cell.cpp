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

Cell::Cell() : row(0), column(0), value(invalid) {}

Cell::Cell(int row, int column, char value) : row(row), column(column) {
    for (int i = 0; i < 4; i++) {
        if (value == printableValues[i]) {
            this->value = static_cast<Value>(i);
        }
    }
}

Cell::Cell(int row, char column, char value) : row(row) {
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
    for (int i = 0; i < 4; i++) {
        if (value == printableValues[i]) {
            this->value = static_cast<Value>(i);
        }
    }
}

Cell::Cell(int row, int column, Value value) : row(row), column(column), value(value) {}

// Big 3
Cell::Cell(const Cell& cell) : row(cell.row), column(cell.column), value(cell.value) {}

Cell& Cell::operator=(const Cell &cell) {
    if (this != &cell) {
        row = cell.row;
        column = cell.column;
        value = cell.value;
    }
    
    return *this;
}

Cell::~Cell() {}


// Get and set
int Cell::getRow() const {
    return row;
}

void Cell::setRow(const int &row) {
    this->row = row;
}

int Cell::getColumn() const {
    return column;
}

void Cell::setColumn(const int &column) {
    this->column = column;
}

Cell::Value Cell::getValue() const {
    return value;
}

void Cell::setValue(const Cell::Value &value) {
    this->value = value;
}


// Testers
bool Cell::isSheep() const {
    return value == sheep;
}

bool Cell::isFox() const {
    return value == fox;
}

bool Cell::isEmpty() const {
    return value == empty;
}

bool Cell::isInvalid() const {
    return value == invalid;
}

void Cell::print(std::ostream &output) const {
    output << printableColumns[column] << printableRows[row];
}

bool Cell::operator==(const Cell &cell) const {
    if (cell.row == row && cell.column == column) {
        return true;
    }
    return false;
}

bool Cell::operator!=(const Cell &cell) const {
    if (cell.row != row || cell.column != column) {
        return true;
    }
    return false;
}

