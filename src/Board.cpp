//
//  Board.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>

#include "Board.h"

void Board::print(BoardLayout boardLayout) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            Coordinate coordinate(i, j);
            Coordinate nextCoordinate(i, j + 1);
            std::cout << boardLayout.getValueAt(coordinate);
            if (boardLayout.isValidCoordinate(coordinate)) {
                if (boardLayout.isValidCoordinate(nextCoordinate)) {
                    std::cout << '-';
                }
            } else {
                std::cout << INVALID_SPACE;
            }
        }
        std::cout << std::endl;
        if (i < 6) {
            std::cout << printDirectionalLinesForRow(i) << std::endl;
        }
        
    }
}

std::string Board::printDirectionalLinesForRow(int row) {
    std::string result = "";
    switch (row) {
        case 0:
            result = "    |\\|/|    ";
            break;
        case 1:
            result = "    |/|\\|    ";
            break;
        case 2:
            result = "|\\|/|\\|/|\\|/|";
            break;
        case 3:
            result = "|/|\\|/|\\|/|\\|";
            break;
        case 4:
            result = "    |\\|/|    ";
            break;
        case 5:
            result = "    |/|\\|    ";
            break;
        default:
            break;
    }
    
    return result;
}