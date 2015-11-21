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
    std::string inputData = "";
    while (!gameHasBeenWon()) {
        updateCurrentPlayer();
        playOneFullTurn(inputData);
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
    std::getline(input, nextLine);
    boardLayout = BoardLayout(layout);
    if (!gameHasBeenWon()) {
        updateCurrentPlayer();
        playOneFullTurn(nextLine);
        if (!gameHasBeenWon()) {
            updateCurrentPlayer();
            playOneFullTurn(nextLine);
        } else {
            printWinner();
        }
    } else {
        printWinner();
    }
    board.print(boardLayout);
}

void GameManager::playOneFullTurn(std::string inputData) {
    board.print(boardLayout);
    Move move = getValidMove(inputData);
    makeMove(move);
}

bool GameManager::gameHasBeenWon() {
    
    if (boardLayout.sheepRemaining() < 9 || boardLayout.isPaddockFull()) {
        return true;
    }
    
    return false;
}

void GameManager::printWinner() {
    if (boardLayout.sheepRemaining() < 9) {
        foxPlayer.won();
    } else {
        sheepPlayer.won();
    }
}

void GameManager::makeMove(Move move) {
    boardLayout.applyMove(move);
}

Move GameManager::getValidMove(std::string inputData) {
    std::string message = "";
    bool isTest = false;
    
    if (inputData.length()) {
        message = inputData;
        isTest = true;
    }
    
    Move move = currentPlayer->getMove(boardLayout, message, isTest);
    while (!validMove(move)) {
        message = "That is not a legal move.";
        move = currentPlayer->getMove(boardLayout, message, isTest);
    }
    
    return move;
}

bool GameManager::validMove(Move move) {
    if (typeid(*currentPlayer) == typeid(SheepPlayer)) {
        if (move.jumps[0].start.value == FOX_CHARACTER) {
            return false;
        }
    }
    return boardLayout.isValidMove(move);
}

void GameManager::updateCurrentPlayer() {
    if (typeid(*currentPlayer) == typeid(SheepPlayer)) {
        currentPlayer = &foxPlayer;
    } else {
        currentPlayer = &sheepPlayer;
    }
}
