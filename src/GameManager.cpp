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

// Big 3
GameManager::GameManager(const GameManager &gameManager) : board(gameManager.board), currentPlayer(gameManager.currentPlayer), foxPlayer(gameManager.foxPlayer), sheepPlayer(gameManager.sheepPlayer) {}

GameManager& GameManager::operator=(const GameManager &gameManager) {
    if (this != &gameManager) {
        board = gameManager.board;
        currentPlayer = gameManager.currentPlayer;
        foxPlayer = gameManager.foxPlayer;
        sheepPlayer = gameManager.sheepPlayer;
    }
    
    return *this;
}

GameManager::~GameManager() {
    currentPlayer = nullptr;
    delete currentPlayer;
}

void GameManager::play() {
    std::ifstream input;
    while (!gameHasBeenWon()) {
        updateCurrentPlayer();
        playOneFullTurn(input);
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
    board = Board(layout);
    if (!gameHasBeenWon()) {
        updateCurrentPlayer();
        playOneFullTurn(input);
        if (!gameHasBeenWon()) {
            updateCurrentPlayer();
            playOneFullTurn(input);
        } else {
            printWinner();
        }
    } else {
        printWinner();
    }
    std::cout << board;
}

void GameManager::playOneFullTurn(std::ifstream &input) {
    std::cout << board;
    Move move = getValidMove(input);
    makeMove(move);
}

bool GameManager::gameHasBeenWon() const {
    
    if (board.sheepRemaining() < 9 || board.isPaddockFull()) {
        return true;
    }
    
    return false;
}

void GameManager::printWinner() const {
    if (board.sheepRemaining() < 9) {
        foxPlayer.won();
    } else {
        sheepPlayer.won();
    }
}

void GameManager::makeMove(const Move &move) {
    board.applyMove(move);
}

Move GameManager::getValidMove(std::ifstream &input) const {
    std::string message;
    std::string testData;
    
    if (input.good()) {
        std::getline(input, testData);
    }
    
    Move move = currentPlayer->getMove(board, message, testData);
    while (!validMove(move)) {
        if (input.good()) {
            std::getline(input, testData);
        }
        message = "That is not a legal move.";
        move = currentPlayer->getMove(board, message, testData);
    }
    
    return move;
    
    
//    std::string message;
//    std::getline(input, message);
//    bool isTest = false;
//    
//    if (message.length()) {
//        isTest = true;
//    }
//    
//    Move move = currentPlayer->getMove(board, message, isTest);
//    while (!validMove(move)) {
//        if (isTest) {
//            std::getline(input, message);
//        } else {
//            message = "That is not a legal move.";
//        }
//        move = currentPlayer->getMove(board, message, isTest);
//    }
//    
//    return move;
}

bool GameManager::validMove(const Move &move) const {
    if (typeid(*currentPlayer) == typeid(SheepPlayer)) {
        if (move.getJumps()[0].getStart().isFox()/* || move.getJumps()[0].getStart().isEmpty() || move.getJumps()[0].getStart().isInvalid()*/) {
            return false;
        } else {
            return board.isValidMove(move);
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
