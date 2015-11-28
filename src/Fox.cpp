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

// Big 3
Fox::Fox(const Fox &fox) : cell(fox.cell), moves(fox.moves), possibleThreats(fox.possibleThreats), possibleNonThreateningMoves(fox.possibleNonThreateningMoves) {}

Fox& Fox::operator=(const Fox &fox) {
    if (this != &fox) {
        cell = fox.cell;
        moves = fox.moves;
        possibleThreats = fox.possibleThreats;
        possibleNonThreateningMoves = fox.possibleNonThreateningMoves;
    }
    
    return *this;
}

Fox::~Fox() {}

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
        if (Move(*iterator).getJumps().size() > moveToBeUsed->getJumps().size()) {
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
        if (moves.back().getJumps().back().end == jump.start) {
            moves.back().addJump(jump);
        } else {
            Move newMove = moves.back();
            newMove.popLastJump();
            newMove.addJump(jump);
            moves.push_back(newMove);
        }
    } else {
        moves.push_back(Move(jump));
    }
}

