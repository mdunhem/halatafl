//
//  Board.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include "BoardLayout.h"

class Board {
    
    std::string printDirectionalLinesForRow(int row);
    
public:
    
    /**
     * Prints out the board based on the supplied BoardLayout object.
     *
     * @param  {BoardLayout} boardLayout    Object containing locations of sheep and foxes on the board
     * @return {void}
     */
    void print(BoardLayout);
};

#endif /* Board_h */
