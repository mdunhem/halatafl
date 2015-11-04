//
//  FoxPlayer.cpp
//  halatafl
//
//  Created by Sven on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>

#include "FoxPlayer.h"


Move FoxPlayer::getMove(BoardLayout boardLayout, std::string message) {
    
    std::vector<Coordinate> foxCoordinates = boardLayout.getFoxCoordinates();
    
    foxOne.location = foxCoordinates[0];
    foxTwo.location = foxCoordinates[1];
    
    Move move;
    Coordinate start(7, 'e');
    Coordinate end(6, 'e');
    Jump jump;
    jump.start = start;
    jump.end = end;
    
    move.jumps.push_back(jump);
    return move;
}

void FoxPlayer::won() {
    std::cout << "The foxes have won!" << std::endl;
}