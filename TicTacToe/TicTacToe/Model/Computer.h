//
//  Computer.h
//  TicTacToe
//
//  Created by Om on 25/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#ifndef __TicTacToe__Computer__
#define __TicTacToe__Computer__

#include <iostream>
#include "Player.h"


class Computer : public Player {
protected:
    
    int tryWin();
    int tryBlock();
    int tryFork();
    int tryCenter();
    int tryCorner();
    int trySide();

    
    int tryWinRow();
    int tryWinColumn();
    int tryWinDiagonally();
    
    int getOpponenetsPositionCountInRow(int iRow, int *iFirstEmptyPos/*out value*/);
    int getOpponenetsPositionCountInCol(int iCol, int *iFirstEmptyPos/*out value*/);
    
public:
    Computer(TicTacToeGame *pGame):Player(pGame) {}
    Computer():Player(){}
    ~Computer(){}
    
    virtual int getChoice();
};

#endif /* defined(__TicTacToe__Computer__) */