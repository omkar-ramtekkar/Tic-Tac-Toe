//
//  TicTacToeGame.cpp
//  TicTacToe
//
//  Created by Om on 25/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

//////////////////////////////////////////////////////////////////
/*
--------------------------
1      |2      |3      |
top    |  top  |       |
left   | middle|       |
--------------------------
4      |5      |6      |
left   |center |       |
middle  |       |       |
--------------------------
7      |8      |9      |
bottom |       |       |
left  |       |       |
--------------------------
 */
//////////////////////////////////////////////////////////////////


#include "TicTacToeGame.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Constant.h"


TicTacToeGame * TicTacToeGame::gameWithTwoPlayer()
{
    class Player *player1 = new Human;
    class Player *player2 = new Human;
    
    player1->setSign('*');
    player2->setSign('#');
    
    return new TicTacToeGame(player1, player2);
}

TicTacToeGame * TicTacToeGame::gameWithOnePlayer()
{
    Player *player1 = new Human;
    Player *player2 = new Computer;
    
    player1->setSign('*');
    player2->setSign('#');
    
    return new TicTacToeGame(player1, player2);
}

void TicTacToeGame::initializeBoard()
{
    if (!getBoard())
    {
        m_board = new BoardValueType*[BOARD_SIZE];

        for (int i=0; i<BOARD_SIZE; ++i)
        {
            m_board[i] = new BoardValueType[BOARD_SIZE];
        }
    }
    
    for (int i=0; i<BOARD_SIZE; ++i)
    {
        for (int j=0; j<BOARD_SIZE; ++j)
        {
            setBoardValue(EMPTY, i, j);
        }
    }
}

void TicTacToeGame::restartGame()
{
    initializeBoard();
}


void TicTacToeGame::setUserInputContext(IInputValueContext *pInputContext)
{
    if (pInputContext && getPlayer1() && getPlayer2())
    {
        getPlayer1()->setInputContext(pInputContext);
        getPlayer2()->setInputContext(pInputContext);
    }
    else
    {
        if (!pInputContext) { std::string("Invalid IInputValueContext passed to setUserInputContext"); }
        if (!pInputContext) { std::string("Game Players are not initialized"); }
    }
}

void TicTacToeGame::displayBoard() const
{
    printf("\n\n\n\n\n\n\n\n\n\n");
    for(int i=0; i<BOARD_SIZE; ++i)
    {
        printf("\n");
        for (int k=0; k<BOARD_SIZE; ++k)
        {
            printf("  |  ");
        }
        printf("\n");
        for (int j=0; j<BOARD_SIZE; ++j)
        {
            BoardValueType value = getBoardElement(i, j);
            if (value == EMPTY)
            {
                printf("  |  ");
            }
            else
            {
                printf("%c |  ", value);
            }
        }
        
        printf("\n");
        for (int k=0; k<BOARD_SIZE; ++k)
        {
            printf("  |  ");
        }
        
        printf("\n");
        
        for (int k=0; k<BOARD_SIZE; ++k)
        {
            printf("----");
        }
    }
}

int TicTacToeGame::playTurn(PlayerID player)
{
    try
    {
        //Now only supported for max two players
        int iChoice = INVALID_INPUT;
        if (player == Player1)
        {
            iChoice = getPlayer1()->getChoice();
        }
        else if(player == Player2)
        {
            iChoice = getPlayer2()->getChoice();
        }
        
        updateBoard(player, iChoice);
        
        return iChoice;
    }
    catch (...)
    {
        return INVALID_INPUT;
    }
}

void TicTacToeGame::updateBoard(int iPlayer, int iChoice)
{
    int i = (iChoice / BOARD_SIZE) + ((iChoice % BOARD_SIZE) != 0 ? 1 : 0);
    int j = (iChoice % BOARD_SIZE) == 0 ? BOARD_SIZE : (iChoice % BOARD_SIZE);
    
    //iChoice is 1 indexed based and i,j are 0 indexed based. So we need to do -1 from both
    --i;
    --j;
    
    if (getBoardElement(i, j) != EMPTY)
    {
        throw std::string("Trying to update already assigned field");
    }
    
    if (iPlayer == Player1)
    {
        setBoardValue(getPlayer1()->getSign(), i, j);
    }
    else
    {
        setBoardValue(getPlayer2()->getSign(), i, j);
    }
}

bool TicTacToeGame::isGameOver() const
{
    displayBoard();
    
    bool bGameOver = checkColumns();
    bGameOver |= checkRows();
    bGameOver |= checkDiagonals();
    return bGameOver;
}

bool TicTacToeGame::isGameDrawn() const
{
    bool bDrawn = true;
    for (int i=0; i<BOARD_SIZE; ++i)
    {
        for (int j=0; j<BOARD_SIZE; ++j)
        {
            if (getBoardElement(i, j) == EMPTY)
            {
                bDrawn = false;
                break;
            }
        }
    }
    
    return bDrawn;
}

bool TicTacToeGame::checkRows() const
{
    bool bSame = true;
    for (int i=0; i<BOARD_SIZE; ++i)
    {
        bSame = true;
        BoardValueType sign = getBoardElement(i, 0);
        for (int j=0; j<BOARD_SIZE; ++j)
        {
            BoardValueType value = getBoardElement(i, j);
            bSame &= ((value != EMPTY) && value == sign);
        }
        
        if (bSame)
        {
            break;
        }
    }
    
    return bSame;
}

bool TicTacToeGame::checkColumns() const
{
    bool bSame = true;
    for (int j=0; j<BOARD_SIZE; ++j)
    {
        bSame = true;
        BoardValueType sign = getBoardElement(0, j);
        for (int i=0; i<BOARD_SIZE; ++i)
        {
            BoardValueType value = getBoardElement(i, j);
            bSame &= ((value != EMPTY) && value == sign);
        }
        
        if (bSame)
        {
            break;
        }
    }
    
    return bSame;
}


bool TicTacToeGame::checkDiagonals() const
{
    BoardValueType sign = getBoardElement(0, 0);
    bool bSame = true;
    for (int i=0; i<BOARD_SIZE; ++i)
    {
        BoardValueType value = getBoardElement(i, i);
        bSame &= (value == sign && value != EMPTY);
    }
    
    if (!bSame)
    {
        bSame = true;
        int iSize = 2;
        BoardValueType sign = getBoardElement(0, iSize);
        for (int i=iSize; i>=iSize; --i)
        {
            BoardValueType value = getBoardElement(i, iSize - i);
            bSame &= ((value != EMPTY) && value == sign);
        }
    }
    
    return bSame;
}


int TicTacToeGame::getCenterValue() const
{
    return getBoardElement(1, 1);
}

int TicTacToeGame::getTopLeftCornerValue() const
{
    return getBoardElement(0, 0);
}

int TicTacToeGame::getTopRightCornerValue() const
{
    return getBoardElement(0, 2);;
}

int TicTacToeGame::getBottomLeftCornerValue() const
{
    return getBoardElement(2, 0);;
}

int TicTacToeGame::getBottomRightCornerValue() const
{
    return getBoardElement(2, 2);
}

int TicTacToeGame::getMiddleLeftSideValue() const
{
    return getBoardElement(1, 0);
}

int TicTacToeGame::getMiddleTopSideValue() const
{
    return getBoardElement(0, 1);
}

int TicTacToeGame::getMiddleRightSideValue() const
{
    return getBoardElement(1, 2);
}

int TicTacToeGame::getMiddleBottomSideValue() const
{
    return getBoardElement(2, 1);
}


int TicTacToeGame::getCenterPosition() const
{
    return 5;
}

int TicTacToeGame::getTopLeftCornerPosition() const
{
    return 1;
}

int TicTacToeGame::getTopRightCornerPosition() const
{
    return 3;
}

int TicTacToeGame::getBottomLeftCornerPosition() const
{
    return 7;
}

int TicTacToeGame::getBottomRightCornerPosition() const
{
    return 9;
}

int TicTacToeGame::getMiddleLeftSidePosition() const
{
    return 4;
}

int TicTacToeGame::getMiddleTopSidePosition() const
{
    return 2;
}

int TicTacToeGame::getMiddleRightSidePosition() const
{
    return 6;
}

int TicTacToeGame::getMiddleBottomSidePosition() const
{
    return 8;
}