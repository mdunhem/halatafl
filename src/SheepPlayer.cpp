//
//  SheepPlayer.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>

#include "SheepPlayer.h"

int convertColumnCharacterToInt(char column) {
    return (int)(column - 'a');
}

int flipRowNumber(int input) {
    return Board::ROWS - input;
}

Move SheepPlayer::getMove(const Board &board, const std::string &message, const std::string &testMove) const {
    int startRow, endRow;
    char startColumn, endColumn;
    std::string input;
    
    if (message.length()) {
        std::cout << message << std::endl;
    }
    
    std::cout << "Your move? ";
    
    if (testMove.length()) {
        input = testMove;
        std::cout << input << std::endl;
    } else {
        std::getline(std::cin, input);
    }
    
    startColumn = convertColumnCharacterToInt(input[0]);
    startRow = flipRowNumber(input[1] - '0');
    endColumn = convertColumnCharacterToInt(input[3]);
    endRow = flipRowNumber(input[4] - '0');
    
    Cell start = board.getCellAtIndex(startRow, startColumn);
    Cell end = board.getCellAtIndex(endRow, endColumn);
    return Move(start, end);
    
    
    
    
    
//    if (!isTest && message.length()) {
//        std::cout << message << std::endl;
//    }
//    
//    std::cout << "Your move? ";
//    
//    if (isTest) {
//        input = message;
//        std::cout << message << std::endl;
//    } else {
//        std::getline(std::cin, input);
//    }
//    
//    startColumn = convertColumnCharacterToInt(input[0]);
//    startRow = flipRowNumber(input[1] - '0');
//    endColumn = convertColumnCharacterToInt(input[3]);
//    endRow = flipRowNumber(input[4] - '0');
//    
//    Cell start = board.getCellAtIndex(startRow, startColumn);
//    Cell end = board.getCellAtIndex(endRow, endColumn);
//    
//    return Move(start, end);
}

void SheepPlayer::won() const {
    std::cout << "The sheep have won!" << std::endl;
}


