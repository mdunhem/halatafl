//
//  Fox.cpp
//  halatafl
//
//  Created by Mike on 11/14/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include "Fox.h"

// Constructors
Fox::Fox() {}

Fox::Fox(Cell cell) : cell(cell) {}

Fox::Fox(const Fox &fox) : cell(fox.cell), moves(fox.moves), possibleThreats(fox.possibleThreats), possibleNonThreateningMoves(fox.possibleNonThreateningMoves) {}

// Getters and setters
Cell Fox::getCell() const {
    return cell;
}
void Fox::setCell(Cell cell) {
    this->cell = cell;
}

Move Fox::getMove() {
    if (moves.empty()) {
        moves.push_back(Move());
    }
    
    Move *moveToBeUsed = &moves.front();
    for (std::vector<Move>::iterator iterator = moves.begin(); iterator != moves.end(); iterator++) {
        if (Move(*iterator).jumps.size() > moveToBeUsed->jumps.size()) {
            *moveToBeUsed = Move(*iterator);
        }
    }
    
    return *moveToBeUsed;
}

std::vector<Move> Fox::getMoves() const {
    return moves;
}

std::vector<Move> Fox::getPossibleThreats() const {
    return possibleThreats;
}

std::vector<Move> Fox::getPossibleNonThreateningMoves() const {
    return possibleNonThreateningMoves;
}

void Fox::addPossibleThreat(Move threat) {
    possibleThreats.push_back(threat);
}

void Fox::addPossibleNonThreateningMove(Move move) {
    possibleNonThreateningMoves.push_back(move);
}

void Fox::addJump(Jump jump) {
    if (moves.size()) {
        if (moves.back().jumps.back().end == jump.start) {
            moves.back().jumps.push_back(jump);
        } else {
            Move newMove = moves.back();
            newMove.jumps.pop_back();
            newMove.jumps.push_back(jump);
            moves.push_back(newMove);
        }
    } else {
        moves.push_back(Move(jump));
    }
}

