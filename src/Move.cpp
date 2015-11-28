//
//  Move.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Move.h"
#include "Board.h"

Jump::Jump() {}

Jump::Jump(Cell start, Cell end) : start(start), end(end) {}

Jump::Jump(Cell start, Cell end, Cell jumpedCell) : start(start), end(end), jumpedCell(jumpedCell) {}

Jump::Jump(const Jump &jump) : start(jump.start), end(jump.end), jumpedCell(jump.jumpedCell) {}

bool Jump::isCaptureJump() {
    if (!jumpedCell.isInvalid()) {
        return true;
    }
    return false;
}

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
