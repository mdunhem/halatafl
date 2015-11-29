//
//  Move.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Move.h"
#include "Board.h"

// Constructors
Move::Move() {}

Move::Move(Cell start, Cell end) {
    jumps.push_back(Jump(start, end));
}

Move::Move(Jump jump) {
    jumps.push_back(jump);
}

// Big 3
Move::Move(const Move &move) : jumps(move.jumps) {}

Move& Move::operator=(const Move &move) {
    if (this != &move) {
        jumps = move.jumps;
    }
    return *this;
}

Move::~Move() {}

// Get and set
std::vector<Jump> Move::getJumps() const {
    return jumps;
}

void Move::addJump(Jump jump) {
    jumps.push_back(jump);
}

void Move::popLastJump() {
    jumps.pop_back();
}

// Display function
void Move::print(std::ostream &output) const {
    output << jumps.front().getStart() << '-' << jumps.back().getEnd();
}

bool Move::operator<(const Move &rhs) const {
    return jumps.size() < rhs.jumps.size();
}
