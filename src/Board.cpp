//
//  Board.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>

#include "Board.h"

int getReversedRowNumber(int row);

// TODO: This needs to be cleaned up so its not quite so much static strings
void Board::print(BoardLayout boardLayout) {
    for (int i = 0; i < 7; i++) {
        std::cout << getReversedRowNumber(i) << " ";
        std::vector<Cell> cells = boardLayout.cellsForRow(i);
        for (int j = 0; j < cells.size(); j++) {
            Cell cell = cells[j];
            std::cout << cell.value;
            if (cell.value != INVALID_SPACE) {
                if ((j + 1) < cells.size() && cells[j + 1].value != INVALID_SPACE) {
                    std::cout << '-';
                }
            } else {
                std::cout << INVALID_SPACE;
            }
        }
//        for (Cell cell : cells) {
//            std::cout << cell.value;
//        }
        std::cout << std::endl;
        if (i < 6) {
            std::cout << printDirectionalLinesForRow(i) << std::endl;
        }
        
    }
    std::cout << "  a b c d e f g" << std::endl;
}

int getReversedRowNumber(int row) {
    switch (row) {
        case 0:
            return 7;
            break;
        case 1:
            return 6;
            break;
        case 2:
            return 5;
            break;
        case 3:
            return 4;
            break;
        case 4:
            return 3;
            break;
        case 5:
            return 2;
            break;
        default:
            break;
    }
    return 1;
}

std::string Board::printDirectionalLinesForRow(int row) {
    std::string result = "";
    switch (row) {
        case 0:
            result = "      |\\|/|    ";
            break;
        case 1:
            result = "      |/|\\|    ";
            break;
        case 2:
            result = "  |\\|/|\\|/|\\|/|";
            break;
        case 3:
            result = "  |/|\\|/|\\|/|\\|";
            break;
        case 4:
            result = "      |\\|/|    ";
            break;
        case 5:
            result = "      |/|\\|    ";
            break;
        default:
            break;
    }
    
    return result;
}