//
//  Move.hpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Move_h
#define Move_h

#include <vector>
#include <iostream>

#include "Cell.h"
#include "Jump.h"

struct Move {
    
    Move();
    Move(Cell start, Cell end);
    Move(Jump jump);
    Move(const Move &move);
    
    std::vector<Jump> jumps;
    
    void print(std::ostream &output) const;
};

inline std::ostream& operator<<(std::ostream &output, const Move &move) {
    move.print(output);
    return output;
}


#endif /* Move_h */
