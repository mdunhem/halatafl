//
//  Jump.h
//  halatafl
//
//  Created by Mike on 10/26/15.
//  Copyright © 2015 Mikael Dunhem. All rights reserved.
//

#ifndef Jump_h
#define Jump_h

#include "Cell.h"

struct Jump {
    
    Jump();
    Jump(Cell start, Cell end);
    Jump(Cell start, Cell end, Cell jumpedCell);
    Jump(const Jump &jump);
    
    Cell getStart() const;
    Cell getEnd() const;
    Cell getJumpedCell() const;
    
    bool isCaptureJump();
    
private:
    Cell start;
    Cell end;
    Cell jumpedCell;
};

#endif /* Jump_h */
