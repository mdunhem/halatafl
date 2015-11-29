//
//  SheepPlayer.hpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef SheepPlayer_h
#define SheepPlayer_h


#include <string>

#include "Player.h"
#include "Board.h"
#include "Move.h"

class SheepPlayer : public Player {
    
    Move promptForMove() const;
    
public:
    
    /**
     * Prompts the player for a move. If a message is supplied print it first
     * then ask for a move from the human player. Create a Move object using
     * supplied input and return the Move object. Board object is
     * ignored by this function.
     *
     * @param  {Board} board    Object containing locations of sheep and foxes on the board
     * @param  {std::string} message        Possible error message to display before prompting player
     * @return {Move}                       Move to be made by player
     */
    virtual Move getMove(const Board &board, const std::string &message, const std::string &testMove = "") const;
    
    /**
     * Prints out the message that the sheep have won to standard output
     *
     * @return {void}
     */
    virtual void won() const;
};

#endif /* SheepPlayer_h */
