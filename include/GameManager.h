//
//  GameManager.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h

#include "SheepPlayer.h"
#include "Move.h"
#include "BoardLayout.h"
#include "Board.h"
#include "FoxPlayer.h"
#include "SheepPlayer.h"

/**
 * Manages the game and run loop.
 */
class GameManager {
    
    void playOneFullTurn();
    
    /**
     * Determines if the game has been won based on whether there are less than
     * 9 sheep or if the paddock is full.
     *
     * @return {bool}   Whether game has been won.
     */
    bool gameHasBeenWon();
    
    /**
     * Asks current player for a move. Then validates the move and reprompts
     * player if it is not a valid move.
     *
     * @return {Move}   Valid move to be made
     */
    Move getValidMove();
    
    
    bool validMove(Move move);
    
    /**
     * A valid move has been created and this function applies the changes
     * made by the move to the private boardLayout object used as the
     * underlying data structure for the location of all players in the
     * game.
     *
     * @param  {Move} move      Valid move to be applied to the data structure
     * @return {void}
     */
    void makeMove(Move);
    
    /**
     * Determines which player won the game and then calls that
     * player's won() function.
     *
     * @return {void}
     */
    void printWinner();
    
    
    void updateCurrentPlayer();
    
    
    bool isPaddockFull();
    
    
    BoardLayout boardLayout;
    
    
    Board board;
    
    
    Player *currentPlayer;
    
    
    FoxPlayer foxPlayer;
    
    
    SheepPlayer sheepPlayer;
    
public:
    
    /**
     * GameManager constructor. This object apptly manages the game
     * and run loop.
     *
     * @return {void}
     */
    GameManager();
    
    /**
     * Main game loop function. Continues running until the game has been
     * won. Prints the board, asks for a valid move, applies the move,
     * changes player, and then repeats. When game has been won it prints
     * out the winner and the board and then quits the game.
     *
     * @return {void}
     */
    void play();
    
    /**
     * Replaces the main run loop and only runs through one turn for each player.
     * This is used to test functionality with supplied input.
     *
     * @return {void}
     */
    void testDriver();
};


#endif /* GameManager_h */
