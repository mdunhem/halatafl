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
#include <map>

#include "Player.h"
#include "BoardLayout.h"
#include "Move.h"
#include "Fox.h"

class FoxPlayer : public Player {
    
    Fox foxOne;
    Fox foxTwo;
    
    void determinePossibleMove(BoardLayout boardLayout, Fox &fox);
    
    void search(BoardLayout &boardLayout, Fox &fox);
    void applyJump(BoardLayout &boardLayout, Fox &fox, Cell &jumpToCell, Cell &jumpedCell);
    
public:
    
    /**
     * Determines the best move possible to be made by either fox. Designed to be
     * an aggressive strategy. Message is ignored by this function.
     *
     * @param  {BoardLayout} boardLayout    Object containing lobations of sheep and foxes on the board
     * @param  {std::string} message        Possible error message to display
     * @return {Move}                       Move to be made by player
     */
    virtual Move getMove(BoardLayout, std::string, bool isTest);
    
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
//        BoardLayout boardLayout;
//        std::vector<Move> possibleThreats;
//        std::map<Direction, Cell> surroundingValues;
//        
//        void determineSurroundingValues(BoardLayout &boardLayout);
//    };
//    
//    Fox foxOne;
//    Fox foxTwo;
//    
//    void determinePossibleMove(BoardLayout &boardLayout, Fox &fox);
//    
//public:
//    
//    /**
//     * Determines the best move possible to be made by either fox. Designed to be
//     * an aggressive strategy. Message is ignored by this function.
//     *
//     * @param  {BoardLayout} boardLayout    Object containing lobations of sheep and foxes on the board
//     * @param  {std::string} message        Possible error message to display
//     * @return {Move}                       Move to be made by player
//     */
//    virtual Move getMove(BoardLayout, std::string);
//    
//    /**
//     * Prints out the message that the foxes have won to standard output
//     *
//     * @return {void}
//     */
//    virtual void won();
//};

#endif /* FoxPlayer_h */
