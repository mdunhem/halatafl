//
//  main.cpp
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "GameManager.h"

int main(int argc, const char* argv[]) {
    GameManager gameManager;
    
    if (argc > 1) {
        std::ifstream input(argv[1]);
        gameManager.testDriver(input);
    } else {
        gameManager.play();
    }
    
    return 0;
}

