//
//  BoardLayout.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef BoardLayout_h
#define BoardLayout_h

#include <iostream>

#include "Cell.h"
#include "Move.h"

const char INVALID_SPACE = ' ';
const char EMPTY_SPACE = '.';
const char FOX_CHARACTER = 'F';
const char SHEEP_CHARACTER = 'S';

//struct BoardValue {
//    const char InvalidSpace = ' ';
//    const char EmptySpace = '.';
//    const char Fox = 'F';
//    const char Sheep = 'S';
//};

//enum Direction {
//    up, down, left, right, upLeft, upRight, downLeft, downRight
//};

class BoardLayout {
    
    std::vector<std::vector<Cell>> layout;
    
    bool isValidJump(Jump jump);
    
    std::string printDirectionalLinesForRow(int row) const;
    
public:
    
    /**
     * Value of each position on the Board
     */
    enum BoardValue {
        invalid, empty, sheep, fox
    };
    
    enum Direction {
        up, down, left, right, upLeft, upRight, downLeft, downRight
    };
    
    static const int ROWS;
    static const int COLS;
    
    BoardLayout();
    BoardLayout(char layout[7][7]);
    BoardLayout(const BoardLayout& layout);
    
    Cell getCellAtIndex(int x, int y);
    Cell getCellInDirectionFromCell(Direction direction, Cell &cell);
    std::vector<Cell> cellsForRow(int row);
    
    void applyMove(Move move);
    void makeJump(Jump jump);
    
    bool isValidMove(Move move);
    
    bool isPaddockFull();
    int sheepRemaining();
    
    std::vector<Cell> getFoxCells();
    
    /**
     * Prints out the board using supplied output stream
     *
     * @return {void}
     */
    void print(std::ostream &output) const;
};

inline std::ostream& operator<<(std::ostream &output, const BoardLayout &boardLayout) {
    boardLayout.print(output);
    return output;
}

#endif /* BoardLayout_h */
