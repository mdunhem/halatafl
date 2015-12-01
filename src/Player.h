//
//  Player.hpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <string>

#include "Board.h"
#include "Move.h"

/**
 * Interface that any player object must implement. Since each player will have a different
 * implementation of these functions, it does not make sense to define them here.
 */
class Player {
public:
    virtual ~Player() {};
    virtual Move getMove(const Board&, const std::string&, const std::string &testMove = "") const = 0;
    virtual void won() const = 0;
};

#endif /* Player_h */
