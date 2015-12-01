//
//  Fox.h
//  halatafl
//
//  Created by Mike on 11/14/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Fox_h
#define Fox_h

#include <map>

#include "Cell.h"
#include "Move.h"
#include "Jump.h"

struct Fox {
    
    Fox();
    Fox(Cell cell);
    
    // Big 3
    Fox(const Fox &fox);
    Fox& operator=(const Fox &fox);
    ~Fox();
    
    Cell getCell() const;
    void setCell(const Cell &cell);
    
    Move* getMove();
    std::vector<Move> getMoves() const;
    
    std::vector<Move> getPossibleThreats() const;
    std::vector<Move> getPossibleNonThreateningMoves() const;
    void addPossibleThreat(Move threat);
    void addPossibleNonThreateningMove(Move move);
    
    void addJump(Jump jump);
    
    bool operator<(const Fox &rhs) const;
    
private:
    Cell cell;
    std::vector<Move> moves;
    std::vector<Move> possibleThreats;
    std::vector<Move> possibleNonThreateningMoves;
};

#endif /* Fox_h */
