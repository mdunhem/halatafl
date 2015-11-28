//
//  GameManager.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <typeinfo>
#include <iostream>

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
    std::cout << board;
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
    board = Board(layout);
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
    std::cout << board;
}

void GameManager::playOneFullTurn(std::string inputData) {
    std::cout << board;
    Move move = getValidMove(inputData);
    makeMove(move);
}

bool GameManager::gameHasBeenWon() {
    
    if (board.sheepRemaining() < 9 || board.isPaddockFull()) {
        return true;
    }
    
    return false;
}

void GameManager::printWinner() {
    if (board.sheepRemaining() < 9) {
        foxPlayer.won();
    } else {
        sheepPlayer.won();
    }
}

void GameManager::makeMove(Move move) {
    board.applyMove(move);
}

Move GameManager::getValidMove(std::string inputData) {
    std::string message = "";
    bool isTest = false;
    
    if (inputData.length()) {
        message = inputData;
        isTest = true;
    }
    
    Move move = currentPlayer->getMove(board, message, isTest);
    while (!validMove(move)) {
        message = "That is not a legal move.";
        move = currentPlayer->getMove(board, message, isTest);
    }
    
    return move;
}

bool GameManager::validMove(Move move) {
    if (typeid(*currentPlayer) == typeid(SheepPlayer)) {
        if (move.getJumps()[0].getStart().isFox() || move.getJumps()[0].getStart().isEmpty() || move.getJumps()[0].getStart().isInvalid()) {
            return false;
        }
    }
    return true;
}

void GameManager::updateCurrentPlayer() {
    if (typeid(*currentPlayer) == typeid(SheepPlayer)) {
        currentPlayer = &foxPlayer;
    } else {
        currentPlayer = &sheepPlayer;
    }
}
