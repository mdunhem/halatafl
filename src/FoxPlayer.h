//
//  FoxPlayer.hpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef FoxPlayer_h
#define FoxPlayer_h

#include <string>

#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Fox.h"

class FoxPlayer : public Player {
    
    Fox searchForJumps(Board board, Fox fox, Board::Direction direction, Cell cellToJump) const;
    Fox searchForThreats(Board board, Fox fox, Cell cellToSearchFrom) const;
    Fox searchForMoves(Board board, Fox fox) const;
    
public:
    
    /**
     * Determines the best move possible to be made by either fox. Designed to be
     * an aggressive strategy. Message is ignored by this function.
     *
     * @param  {Board} board    Object containing lobations of sheep and foxes on the board
     * @param  {std::string} message        Possible error message to display
     * @return {Move}                       Move to be made by player
     */
    virtual Move getMove(const Board &board, const std::string &message, const std::string &testMove = "") const;
    
    /**
     * Prints out the message that the foxes have won to standard output
     *
     * @return {void}
     */
    virtual void won() const;
};

#endif /* FoxPlayer_h */
