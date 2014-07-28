//
//  Human.h
//  TicTacToe
//
//  Created by Om on 29/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#ifndef __TicTacToe__Human__
#define __TicTacToe__Human__

#include <iostream>
#include "Player.h"

class TicTacToeGame;

class Human : public Player
{
    
public:
    Human(TicTacToeGame *pGame) :Player(pGame){}
    Human():Player(){}
    Human(void *pContext):Player(){}
    virtual int getChoice();
};

#endif /* defined(__TicTacToe__Human__) */
