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
    
    /**
     * Gets a copy of all jumps this move can make.
     *
     * @return vector<Jump>
     */
    std::vector<Jump> getJumps() const;

    /**
     * Adds a jump to the end of move.
     * 
     * @param jump
     */
    void addJump(Jump jump);

    /**
     * Removes that last jump added to this move
     */
    void popLastJump();
    
    /**
     * Properly formats this move and prints it to the supplied output stream.
     * 
     * @param output            Output stream to print to
     */
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
