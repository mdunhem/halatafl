//
//  Cell.h
//  halatafl
//
//  Created by Mike on 11/13/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Cell_h
#define Cell_h

#include <iostream>

struct Cell {
    
    /**
     * Value of each position on the Board
     */
    enum Value {
        invalid = 0, empty, sheep, fox
    };
    
    int row;
    int column;
    char value;
    
    Value cellValue;
    
    static const char printableValues[];
    static const char printableColumns[];
    static const int printableRows[];
    
    Cell();
    Cell(int row, int column, char value);
    Cell(int row, char column, char value);
    Cell(int row, int column, Value value);
    //    Cell(const Cell& cell);
    
    bool isSheep() const;
    bool isFox() const;
    bool isEmpty() const;
    bool isInvalid() const;
    
    void print(std::ostream &output) const;
    
    bool operator==(const Cell &cell) const;
    bool operator!=(const Cell &cell) const;
    
private:
    int printableRow() const;
    char getColumnCharacter() const;
};

inline std::ostream& operator<<(std::ostream &output, const Cell &cell) {
    cell.print(output);
    return output;
}

inline std::ostream& operator<<(std::ostream &output, const Cell::Value &value) {
    output << Cell::printableValues[value];
    return output;
}

#endif /* Cell_h */
