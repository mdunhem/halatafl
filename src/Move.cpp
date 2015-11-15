//
//  Move.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Move.h"

Move::Move() {
    
}

Move::Move(Cell start, Cell end) {
    Jump jump;
    jump.start = start;
    jump.end = end;
    
    jumps.push_back(jump);
}

void Move::print(std::ostream &output) const {
    output << jumps.front().start << '-' << jumps.back().end;
}
