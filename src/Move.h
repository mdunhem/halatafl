//
//  Move.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Move_h
#define Move_h

#include <vector>
#include "Coordinate.h"
#include "Cell.h"
#include "BoardLayout.h"


struct Jump {
    Coordinate start;
    Coordinate end;
    Cell startingCell;
    Cell endingCell;
};

struct Move {
    
    Move();
    Move(char startColumn, int startRow, char endColumn, int endRow);
    
    std::vector<Jump> jumps;
};


#endif /* Move_h */
