//
//  Player.h
//  TicTacToe
//
//  Created by Om on 25/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#ifndef __TicTacToe__Player__
#define __TicTacToe__Player__

#include <iostream>

class TicTacToeGame;

typedef enum
{
    HumanPlayer = 0,
    ComputerPlayer
}PlayerType;


class IInputValueContext
{
public:
    IInputValueContext(){}
    virtual ~IInputValueContext(){}
    
public:
    virtual int getChoice() = 0;
};

class Player
{
    
protected:
    PlayerType m_type;
    int m_iSign;
    IInputValueContext *m_pInputContext;
    TicTacToeGame *m_pGame;
    
public:
    
    Player(TicTacToeGame *pGame):m_iSign(-1), m_pGame(pGame){}
    Player():m_iSign(-1), m_pGame(NULL), m_pInputContext(NULL) {}
    
    virtual ~Player() { m_pGame = NULL; }
    
    TicTacToeGame* getGame() { return m_pGame; }
    void setGame(TicTacToeGame *pGame) { m_pGame = pGame; }
    PlayerType getType() const { return m_type; }
    virtual int getChoice() = 0;
    virtual int getSign() { return m_iSign; }
    virtual void setSign(int iSign) { m_iSign = iSign; }
    
    virtual void setInputContext(IInputValueContext *pContext) { m_pInputContext = pContext; }
    IInputValueContext * getInputContext() { return m_pInputContext; }
};

#endif /* defined(__TicTacToe__Player__) */
