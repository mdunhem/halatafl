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
    
    static const char printableValues[];
    static const char printableColumns[];
    static const int printableRows[];
    
    Cell();
    Cell(int row, int column, char value);
    Cell(int row, char column, char value);
    Cell(int row, int column, Value value);
    
    // Big 3
    Cell(const Cell& cell);
    Cell& operator=(const Cell &cell);
    ~Cell();
    
    // Getters and setters
    int getRow() const;
    void setRow(const int &row);
    
    int getColumn() const;
    void setColumn(const int &column);
    
    Value getValue() const;
    void setValue(const Value &value);
    
    // Value tests
    bool isSheep() const;
    bool isFox() const;
    bool isEmpty() const;
    bool isInvalid() const;
    
    // Prints out the cell value
    void print(std::ostream &output) const;
    
    bool operator==(const Cell &cell) const;
    bool operator!=(const Cell &cell) const;
    
private:
    int row;
    int column;
    Value value;
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
