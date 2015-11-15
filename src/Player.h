//
//  Player.hpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <string>

#include "BoardLayout.h"
#include "Move.h"


class Player {
public:
    virtual ~Player() {};
    virtual Move getMove(BoardLayout, std::string, bool isTest) = 0;
    virtual void won() = 0;
};

#endif /* Player_h */
