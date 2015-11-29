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
    
    // Big 3
    Move(const Move &move);
    Move& operator=(const Move &move);
    ~Move();
    
    std::vector<Jump> getJumps() const;
    void addJump(Jump jump);
    void popLastJump();
    
    void print(std::ostream &output) const;
    
    bool operator<(const Move &rhs) const;
    
private:
    std::vector<Jump> jumps;
};

inline std::ostream& operator<<(std::ostream &output, const Move &move) {
    move.print(output);
    return output;
}


#endif /* Move_h */
