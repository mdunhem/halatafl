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

struct Fox {
    
//    Board board;
    Cell cell;
//    Cell *currentLocation;
    std::vector<Move> moves;
    std::vector<Move> possibleThreats;
    std::vector<Move> possibleNonThreateningMoves;
//    std::map<Board::Direction, Cell> surroundingValues;
    
public:
    
    Fox();
    Fox(Board board, Cell cell);
    Fox(const Fox &fox);
    
    Cell getCell() const;
    void setCell(Cell cell);
    
    Move getMove();
    
//    Board getBoard() const;
//    void setBoard(Board board);
    
    std::vector<Move> getPossibleThreats() const;
    std::vector<Move> getPossibleNonThreateningMoves() const;
    void addPossibleThreat(Move threat);
    void addPossibleNonThreateningMove(Move move);
    
//    void determineSurroundingValues(Board &board);
//    std::map<Board::Direction, Cell> getSurroundingValuesWithRadius(Board &board, int radius);
    
    void addJump(Jump jump);
    
private:
    Move move;
};

#endif /* Fox_h */
