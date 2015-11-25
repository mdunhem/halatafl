//
//  Board.hpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Board_h
#define Board_h

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

class Board {
    
    std::vector<std::vector<Cell>> layout;
    
    bool isValidJump(Jump jump);
    
    std::string printDirectionalLinesForRow(int row) const;
    
public:
    
    enum Direction {
        up, down, left, right, upLeft, upRight, downLeft, downRight
    };
    
    static const int ROWS;
    static const int COLS;
    
    Board();
    Board(char layout[7][7]);
    Board(const Board& layout);
    
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

inline std::ostream& operator<<(std::ostream &output, const Board &board) {
    board.print(output);
    return output;
}

#endif /* Board_h */
