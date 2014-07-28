//
//  TicTacToeGame.h
//  TicTacToe
//
//  Created by Om on 25/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#ifndef __TicTacToe__TicTacToeGame__
#define __TicTacToe__TicTacToeGame__

#include <iostream>
#include "Player.h"

typedef int BoardValueType;

typedef enum
{
    Player1 = 1,
    Player2,
    PlayerCount //HINT - This will give the number of players
}PlayerID;

class TicTacToeGame {
    
private:
    BoardValueType **m_board;
    Player *m_pPlayer1;
    Player *m_pPlayer2;
    
private:
    
    TicTacToeGame(Player *player1, Player *player2):m_board(NULL), m_pPlayer1(player1), m_pPlayer2(player2)
    {
        m_pPlayer1->setGame(this);
        m_pPlayer2->setGame(this);
    }
    
    void initializeBoard();
    
protected:
    void displayBoard() const;
    
    Player * getPlayer1() { return m_pPlayer1; }
    Player * getPlayer2() { return m_pPlayer2; }
    
    void updateBoard(int iPlayer, int iChoice);
    void setBoardValue(BoardValueType value, int row, int column) { m_board[row][column] = value; }
    
    bool checkDiagonals() const;
    bool checkRows() const;
    bool checkColumns() const;
    
public:
    
    ~TicTacToeGame() { delete m_pPlayer1; delete m_pPlayer2; m_pPlayer1 = NULL; m_pPlayer2 = NULL; }
    
    static TicTacToeGame * gameWithOnePlayer();
    static TicTacToeGame * gameWithTwoPlayer();
    
    bool isGameOver() const;
    bool isGameDrawn() const;
    BoardValueType ** const getBoard() const { return m_board; }
    BoardValueType getBoardElement(int row, int column) const { return m_board[row][column]; }
    void setUserInputContext(IInputValueContext *pInputContext);
    
    int playTurn(PlayerID player);
    
    void startNewGame() { initializeBoard(); }
    void restartGame();
    void endGame() { initializeBoard(); }
    
    //////////////
    int getCenterPosition() const;
    int getTopLeftCornerPosition() const;
    int getTopRightCornerPosition() const;
    int getBottomLeftCornerPosition() const;
    int getBottomRightCornerPosition() const;
    int getMiddleLeftSidePosition() const;
    int getMiddleTopSidePosition() const;
    int getMiddleRightSidePosition() const;
    int getMiddleBottomSidePosition() const;
    
    /////////////
    BoardValueType getCenterValue() const;
    BoardValueType getTopLeftCornerValue() const;
    BoardValueType getTopRightCornerValue() const;
    BoardValueType getBottomLeftCornerValue() const;
    BoardValueType getBottomRightCornerValue() const;
    BoardValueType getMiddleLeftSideValue() const;
    BoardValueType getMiddleTopSideValue() const;
    BoardValueType getMiddleRightSideValue() const;
    BoardValueType getMiddleBottomSideValue() const;
};

#endif /* defined(__TicTacToe__TicTacToeGame__) */
