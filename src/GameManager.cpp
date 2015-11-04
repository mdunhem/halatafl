//
//  GameManager.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <typeinfo>

#include "GameManager.h"

//static int runloop = 0;

GameManager::GameManager() {
    currentPlayer = &foxPlayer;
}

void GameManager::play() {
    while (!gameHasBeenWon()) {
        updateCurrentPlayer();
        playOneFullTurn();
    }
    
    printWinner();
    board.print(boardLayout);
}

void GameManager::testDriver() {
    playOneFullTurn();
}

void GameManager::playOneFullTurn() {
    board.print(boardLayout);
    Move move = getValidMove();
    makeMove(move);
}

bool GameManager::gameHasBeenWon() {
    
    if (boardLayout.sheepRemaining() < 9 || boardLayout.isPaddockFull()) {
        return true;
    }
    
    return false;
    
    // This part only here for quick testing
//    if (runloop < 2) {
//        runloop++;
//        return false;
//    }
//    return true;
}

void GameManager::printWinner() {
    currentPlayer->won();
}

void GameManager::makeMove(Move move) {
    if (boardLayout.applyMove(move)) {
        return;
    }
}

Move GameManager::getValidMove() {
    std::string message = "";
    Move move = currentPlayer->getMove(boardLayout, message);
    while (!validMove(move)) {
        message = "That is not a legal move.";
        move = currentPlayer->getMove(boardLayout, message);
    }
    
    return move;
}

bool GameManager::validMove(Move move) {
    return true;
}

void GameManager::updateCurrentPlayer() {
    if (typeid(*currentPlayer) == typeid(SheepPlayer)) {
        currentPlayer = &foxPlayer;
    } else {
        currentPlayer = &sheepPlayer;
    }
}
