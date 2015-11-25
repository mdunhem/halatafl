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
#include "Board.h"

class Fox {
    
    Board boardLayout;
    Cell cell;
    Cell *currentLocation;
    Move move;
    std::vector<Move> possibleThreats;
    std::vector<Move> possibleNonThreateningMoves;
    std::map<Direction, Cell> surroundingValues;
    
public:
    
    Fox();
    Fox(Board boardLayout, Cell cell);
    Fox(const Fox &fox);
    
    Cell getCell() const;
    void setCell(Cell cell);
    
    Move getMove();
    void setMove(Move move);
    
    Board getBoard() const;
    void setBoard(Board boardLayout);
    
    std::vector<Move> getPossibleThreats() const;
    std::vector<Move> getPossibleNonThreateningMoves() const;
    void addPossibleThreat(Move threat);
    void addPossibleNonThreateningMove(Move move);
    
    void determineSurroundingValues(Board &boardLayout);
    std::map<Direction, Cell> getSurroundingValuesWithRadius(Board &boardLayout, int radius);
    
    void findPossibleJump(Board &boardLayout);
    
    void calculateMove();
    
    void addJump(Jump jump);
};

#endif /* Fox_h */
