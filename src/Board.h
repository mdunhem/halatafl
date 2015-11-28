//
//  Board.h
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <iostream>
#include <map>

#include "Cell.h"
#include "Move.h"
#include "Jump.h"

class Board {
    
public:
    
    enum Direction {
        up, down, left, right, upLeft, upRight, downLeft, downRight
    };
    
    static const int ROWS;
    static const int COLS;
    
    Board();
    Board(char layout[7][7]);
    
    // Big 3
    Board(const Board& board);
    Board& operator=(const Board &board);
    ~Board();
    
    Cell getCellAtIndex(const int &x, const int &y) const;
    Cell getCellInDirectionFromCellWithRadius(const Direction &direction, const Cell &cell, const int &radius = 1) const;
    std::map<Direction, Cell> getSurroundingCells(Cell cell);
    
    void applyMove(const Move &move);
    void makeJump(const Jump &jump);
    
    bool isValidMove(const Move &move) const;
    
    bool isPaddockFull() const;
    int sheepRemaining() const;
    
    std::vector<Cell> getFoxCells() const;
    
    /**
     * Prints out the board using supplied output stream
     *
     * @return {void}
     */
    void print(std::ostream &output) const;
    
private:
    
    std::vector<std::vector<Cell> > layout;
    
    bool isValidJump(const Jump &jump) const;
    
    std::string printDirectionalLinesForRow(int row) const;
    
    void cellInDirection(std::map<Direction, Cell> &cells, const Direction &direction, const Cell &cell) const;
};

inline std::ostream& operator<<(std::ostream &output, const Board &board) {
    board.print(output);
    return output;
}

#endif /* Board_h */
