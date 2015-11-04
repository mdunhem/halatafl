//
//  FoxPlayer.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef FoxPlayer_h
#define FoxPlayer_h

#include <string>

#include "Player.h"
#include "BoardLayout.h"
#include "Move.h"

class FoxPlayer : public Player {
    
    struct Fox {
        Coordinate location;
        Move move;
        std::vector<Move> possibleThreats;
    };
    
    Fox foxOne;
    Fox foxTwo;
    
public:
    
    /**
     * Determines the best move possible to be made by either fox. Designed to be
     * an aggressive strategy. Message is ignored by this function.
     *
     * @param  {BoardLayout} boardLayout    Object containing lobations of sheep and foxes on the board
     * @param  {std::string} message        Possible error message to display
     * @return {Move}                       Move to be made by player
     */
    virtual Move getMove(BoardLayout, std::string);
    
    /**
     * Prints out the message that the foxes have won to standard output
     *
     * @return {void}
     */
    virtual void won();
};

#endif /* FoxPlayer_h */
