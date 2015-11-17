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
#include "BoardLayout.h"

enum Direction {
    up, down, left, right, upLeft, upRight, downLeft, downRight
};

class Fox {
    
    Cell cell;
    Move move;
//    BoardLayout boardLayout;
    std::vector<Move> possibleThreats;
    std::map<Direction, Cell> surroundingValues;
    
public:
    
    Fox();
    Fox(/*BoardLayout boardLayout,*/ Cell cell);
    Fox(const Fox &fox);
    
    Cell getCell() const;
    void setCell(Cell cell);
    
    Move getMove() const;
    void setMove(Move move);
    
//    BoardLayout getBoardLayout() const;
//    void setBoardLayout(BoardLayout boardLayout);
    
    std::vector<Move> getPossibleThreats() const;
    
    void determineSurroundingValues(BoardLayout &boardLayout);
    std::map<Direction, Cell> getSurroundingValuesWithRadius(BoardLayout &boardLayout, int radius);
    
    void findPossibleJump(BoardLayout &boardLayout);
};

#endif /* Fox_h */
