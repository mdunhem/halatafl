//
//  GameManager.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <typeinfo>

#include "GameManager.h"

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

void GameManager::testDriver(std::ifstream &input) {
    std::string nextLine;
    char layout[7][7];
    for (int i = 0; i < 7; i++) {
        std::getline(input, nextLine);
        for (int j = 0; j < 7; j++) {
            layout[i][j] = nextLine[j];
        }
    }
    boardLayout = BoardLayout(layout);
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
