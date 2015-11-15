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
    int row;
    int column;
    char value;
    
    Cell();
    Cell(int row, int column, char value);
    Cell(int row, char column, char value);
    //    Cell(const Cell& cell);
    
    void print(std::ostream &output) const;
    
private:
    int printableRow() const;
    char getColumnCharacter() const;
};

inline std::ostream& operator<<(std::ostream &output, const Cell &cell) {
    cell.print(output);
    return output;
}

#endif /* Cell_h */
