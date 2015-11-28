//
//  Move.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Move.h"
#include "Board.h"

Move::Move() {}

Move::Move(Cell start, Cell end) {
    jumps.push_back(Jump(start, end));
}

Move::Move(Jump jump) {
    jumps.push_back(jump);
}

Move::Move(const Move &move) : jumps(move.jumps) {}

void Move::print(std::ostream &output) const {
    output << jumps.front().start << '-' << jumps.back().end;
}
