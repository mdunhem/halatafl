//
//  SheepPlayer.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>

#include "SheepPlayer.h"

int convertColumnCharacterToInt(char column) {
    int result = 0;
    
    switch (column) {
        case 'a': {
            result = 0;
            break;
        }
        case 'b': {
            result = 1;
            break;
        }
        case 'c': {
            result = 2;
            break;
        }
        case 'd': {
            result = 3;
            break;
        }
        case 'e': {
            result = 4;
            break;
        }
        case 'f': {
            result = 5;
            break;
        }
        case 'g': {
            result = 6;
            break;
        }
        default: {
            break;
        }
    }
    
    return result;
}

int flipRowNumber(int input) {
    int row = 0;
    switch (input) {
        case 1: {
            row = 6;
            break;
        }
        case 2: {
            row = 5;
            break;
        }
        case 3: {
            row = 4;
            break;
        }
        case 4: {
            row = 3;
            break;
        }
        case 5: {
            row = 2;
            break;
        }
        case 6: {
            row = 1;
            break;
        }
        case 7: {
            row = 0;
            break;
        }
        default:
            break;
    }
    return row;
}

Move SheepPlayer::getMove(BoardLayout boardLayout, std::string message, bool isTest) {
    int startRow, endRow;
    char startColumn, endColumn;
    std::string input;
    
    if (!isTest && message.length()) {
        std::cout << message << std::endl;
    }
    
    std::cout << "Your move? ";
    
    if (isTest) {
        input = message;
        std::cout << message << std::endl;
    } else {
        std::getline(std::cin, input);
    }
    
    startColumn = convertColumnCharacterToInt(input[0]);
    startRow = flipRowNumber(input[1] - '0');
    endColumn = convertColumnCharacterToInt(input[3]);
    endRow = flipRowNumber(input[4] - '0');
    
    Cell start = boardLayout.getCellAtIndex(startRow, startColumn);
    Cell end = boardLayout.getCellAtIndex(endRow, endColumn);
    
    return Move(start, end);
}

void SheepPlayer::won() {
    std::cout << "The sheep have won!" << std::endl;
}


