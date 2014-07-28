//
//  UserInputContext.h
//  TicTacToe
//
//  Created by Om on 01/02/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#ifndef __TicTacToe__UserInputContext__
#define __TicTacToe__UserInputContext__

#include <iostream>
#include "Player.h"

class UserInputContext : public IInputValueContext
{
    int m_iLastUserChoice;
    
public:
    virtual int getChoice() { return m_iLastUserChoice; }
    void setLastUserChoice(int iLastUserChoice) { m_iLastUserChoice = iLastUserChoice; }
};

#endif /* defined(__TicTacToe__UserInputContext__) */
