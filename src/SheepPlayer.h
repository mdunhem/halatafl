//
//  SheepPlayer.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef SheepPlayer_h
#define SheepPlayer_h


#include <string>

#include "Player.h"
#include "Board.h"
#include "Move.h"

class SheepPlayer : public Player {
    
    Move promptForMove();
    
public:
    
    /**
     * Prompts the player for a move. If a message is supplied print it first
     * then ask for a move from the human player. Create a Move object using
     * supplied input and return the Move object. Board object is
     * ignored by this function.
     *
     * @param  {Board} boardLayout    Object containing locations of sheep and foxes on the board
     * @param  {std::string} message        Possible error message to display before prompting player
     * @return {Move}                       Move to be made by player
     */
    virtual Move getMove(Board, std::string, bool isTest);
    
    /**
     * Prints out the message that the sheep have won to standard output
     *
     * @return {void}
     */
    virtual void won();
};

#endif /* SheepPlayer_h */
