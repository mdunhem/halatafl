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
#include <iostream>

#include "Cell.h"


struct Jump {
    Cell startingCell;
    Cell endingCell;
};

struct Move {
    
    Move();
    Move(Cell start, Cell end);
    
    std::vector<Jump> jumps;
    
    void print(std::ostream &output) const;
};

inline std::ostream& operator<<(std::ostream &output, const Move &move) {
    move.print(output);
    return output;
}


#endif /* Move_h */
