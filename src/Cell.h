//
//  Cell.h
//  halatafl
//
//  Created by Mike on 11/13/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Cell_h
#define Cell_h

struct Cell {
    int row;
    int column;
    char value;
    
    Cell();
    Cell(int row, int column, char value);
    //    Cell(const Cell& cell);
    
    char getColumnCharacter();
    
    //    Cell& operator=(const Cell&);
};

#endif /* Cell_h */
