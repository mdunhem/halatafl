//
//  Fox.cpp
//  halatafl
//
//  Created by Mike on 11/14/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <stdlib.h>
#include <time.h>

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
void Fox::setCell(const Cell &cell) {
    this->cell = cell;
}

Move* Fox::getMove() {
    std::srand(time(NULL));
    
    if (moves.empty()) {
        return nullptr;
    }
    
//    if (moves.empty()) {
//        moves.push_back(Move(cell, cell));
//    }
    
    Move *moveToBeUsed = &moves.front();
    for (Move move : moves) {
        if (move.getJumps().size() > moveToBeUsed->getJumps().size()) {
            *moveToBeUsed = move;
        } else if (move.getJumps().size() == moveToBeUsed->getJumps().size()) {
            *moveToBeUsed = std::rand() % 2 ? move : *moveToBeUsed;
        }
    }
    
//    for (std::vector<Move>::iterator iterator = moves.begin(); iterator != moves.end(); iterator++) {
//        if (Move(*iterator).getJumps().size() > moveToBeUsed->getJumps().size()) {
//            *moveToBeUsed = Move(*iterator);
//        } else if (Move(*iterator).getJumps().size() == moveToBeUsed->getJumps().size()) {
//            *moveToBeUsed = std::rand() % 2 ? Move(*iterator) : *moveToBeUsed;
//        }
//    }
    
    return moveToBeUsed;
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
        if (moves.back().getJumps().back().getEnd() == jump.getStart()) {
            moves.back().addJump(jump);
        } else {
            Move newMove = moves.back();
            while (newMove.getJumps().size() && newMove.getJumps().back().getEnd() != jump.getStart()) {
                newMove.popLastJump();
            }
            newMove.addJump(jump);
            moves.push_back(newMove);
        }
    } else {
        moves.push_back(Move(jump));
    }
}

bool Fox::operator<(const Fox &rhs) const {
    return moves.size() < rhs.moves.size();
}
