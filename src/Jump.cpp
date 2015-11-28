//
//  Jump.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Jump.h"

Jump::Jump() {}

Jump::Jump(Cell start, Cell end) : start(start), end(end) {}

Jump::Jump(Cell start, Cell end, Cell jumpedCell) : start(start), end(end), jumpedCell(jumpedCell) {}

// Big 3
Jump::Jump(const Jump &jump) : start(jump.start), end(jump.end), jumpedCell(jump.jumpedCell) {}

Jump& Jump::operator=(const Jump &jump) {
    if (this != &jump) {
        start = jump.start;
        end = jump.end;
        jumpedCell = jump.jumpedCell;
    }
    
    return *this;
}

Jump::~Jump() {}

// Get. No need for setters
Cell Jump::getStart() const {
    return start;
}

Cell Jump::getEnd() const {
    return end;
}

Cell Jump::getJumpedCell() const {
    return jumpedCell;
}

// Tester
bool Jump::isCaptureJump() {
    if (!jumpedCell.isInvalid()) {
        return true;
    }
    return false;
}