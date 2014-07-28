//
//  Human.cpp
//  TicTacToe
//
//  Created by Om on 29/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#include "Human.h"

int Human::getChoice()
{
    IInputValueContext *pInputContext = getInputContext();
    if (pInputContext)
    {
        return pInputContext->getChoice();
    }
    else
    {
        throw std::string("IInputValueContext not provived for Human Player");
    }
}