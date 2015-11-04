//
//  SheepPlayer.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>

#include "SheepPlayer.h"

Move SheepPlayer::getMove(BoardLayout boardLayout, std::string message) {
    int startRow, endRow;
    char startColumn, endColumn;
    std::string input;
    
    if (message.length()) {
        std::cout << message << std::endl;
    }
    
    std::cout << "Your move? ";
    
    std::getline(std::cin, input);
    
    startColumn = input[0];
    startRow = input[1] - '0';
    endColumn = input[3];
    endRow = input[4] - '0';
    
//    Move move(startColumn, startRow, endColumn, endRow);
    return Move(startColumn, startRow, endColumn, endRow);;
}

void SheepPlayer::won() {
    std::cout << "The sheep have won!" << std::endl;
}
