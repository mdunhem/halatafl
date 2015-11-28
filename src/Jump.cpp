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

Jump::Jump(const Jump &jump) : start(jump.start), end(jump.end), jumpedCell(jump.jumpedCell) {}

bool Jump::isCaptureJump() {
    if (!jumpedCell.isInvalid()) {
        return true;
    }
    return false;
}