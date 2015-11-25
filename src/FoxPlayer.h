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
#include <map>

#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Fox.h"

class FoxPlayer : public Player {
    
    Fox foxOne;
    Fox foxTwo;
    
    void determinePossibleMove(Board board, Fox &fox);
    
    void search(Board &board, Fox &fox);
    void applyJump(Board &board, Fox &fox, Cell &jumpToCell, Cell &jumpedCell);
    
public:
    
    /**
     * Determines the best move possible to be made by either fox. Designed to be
     * an aggressive strategy. Message is ignored by this function.
     *
     * @param  {Board} board    Object containing lobations of sheep and foxes on the board
     * @param  {std::string} message        Possible error message to display
     * @return {Move}                       Move to be made by player
     */
    virtual Move getMove(Board, std::string, bool isTest);
    
    /**
     * Prints out the message that the foxes have won to standard output
     *
     * @return {void}
     */
    virtual void won();
};


//class FoxPlayer : public Player {
//    
//    struct Fox {
//        enum Direction {
//            up, down, left, right, upLeft, upRight, downLeft, downRight
//        };
//        
//        Cell cell;
//        Move move;
//        Board board;
//        std::vector<Move> possibleThreats;
//        std::map<Direction, Cell> surroundingValues;
//        
//        void determineSurroundingValues(Board &board);
//    };
//    
//    Fox foxOne;
//    Fox foxTwo;
//    
//    void determinePossibleMove(Board &board, Fox &fox);
//    
//public:
//    
//    /**
//     * Determines the best move possible to be made by either fox. Designed to be
//     * an aggressive strategy. Message is ignored by this function.
//     *
//     * @param  {Board} board    Object containing lobations of sheep and foxes on the board
//     * @param  {std::string} message        Possible error message to display
//     * @return {Move}                       Move to be made by player
//     */
//    virtual Move getMove(Board, std::string);
//    
//    /**
//     * Prints out the message that the foxes have won to standard output
//     *
//     * @return {void}
//     */
//    virtual void won();
//};

#endif /* FoxPlayer_h */
