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
    
    // Get, set current location
    Cell getCell() const;
    void setCell(const Cell &cell);
    
    /**
     * Gets a pointer to the move with the most jumps possible, i.e. captures the
     * most sheep. This will return nullptr if there are no moves that can be made
     * 
     * @return Move*
     */
    Move* getMove();

    /**
     * Gets a copy of all of the possible capturing moves that can be made by this fox.
     * If this fox cannot capture any sheep, this vector will be empty.
     */
    std::vector<Move> getMoves() const;
    
    /**
     * Vector containing all possible threats that this fox can make.
     */
    std::vector<Move> getPossibleThreats() const;

    /**
     * Vector containing all moves that this fox can make that neither captures a sheep
     * nor makes a threat. If no possible moves can be made, this will at least contain
     * a stationary move.
     */
    std::vector<Move> getPossibleNonThreateningMoves() const;

    /**
     * Adds a threat to the possibleThreats vector
     * @param threat            Move to be added
     */
    void addPossibleThreat(Move threat);

    /**
     * Adds a single space move that neither threatens nor captures a sheep.
     * @param move              Move to be added
     */
    void addPossibleNonThreateningMove(Move move);
    
    /**
     * Adds a capturing jump to the current Move structure. If the jump does not originate
     * from the same cell as the previous jump added, this will create a new Move structure
     * and add it to internal moves vector.
     * 
     * @param jump              The jump to be added
     */
    void addJump(Jump jump);
    
    bool operator<(const Fox &rhs) const;
    
private:
    Cell cell;
    std::vector<Move> moves;
    std::vector<Move> possibleThreats;
    std::vector<Move> possibleNonThreateningMoves;
};

#endif /* Fox_h */
