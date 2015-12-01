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
    
    /**
     * Gets the cell located at the specified x, y coordinates.
     * 
     * @param  {int} x        The row to search for
     * @param  {int} y        The column to search for
     * @return {Cell}
     */
    Cell getCellAtIndex(const int &x, const int &y) const;

    /**
     * Gets the cell located one location passed the cell that is passed in, in the direction
     * specified. The default is to find the adjacent cell but if radius is supplied, will
     * retrieve the cell that is that many spaces away from the cell parameter.
     * 
     * @param  {Direction}  direction   The direction to search in
     * @param  {Cell}       cell        The cell used as the context for the search
     * @param  {int}        radius      How many spaces out the find the cell
     * @return {Cell}
     */
    Cell getCellInDirectionFromCellWithRadius(const Direction &direction, const Cell &cell, const int &radius = 1) const;

    /**
     * Takes a cell object and retrieves all adjoining cells that can be accessed. This will
     * only include directions that can be moved to based on the lines on the game board.
     * i.e. This will not return diagonal directions if the cell is in a location where it
     * can only make an up/down or left/right move.
     *
     * @param  {Cell} cell              The cell used as context for the search
     * @return {map}                    A map object containing all surrounding values
     */
    std::map<Direction, Cell> getSurroundingCells(Cell cell);
    
    /**
     * Applies all of the jumps in the supplied move object to the underlying data structure
     * @param {Move} move               Move to be made
     */
    void applyMove(const Move &move);

    /**
     * Applies a single jump to the underlying data structure
     * @param jump                      Jump to be made
     */
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
    
    /**
     * The underlying data structure
     */
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
