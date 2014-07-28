//
//  Computer.cpp
//  TicTacToe
//
//  Created by Om on 25/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#include "Computer.h"
#include "TicTacToeGame.h"
#include "Constant.h"

#define CHOICE_FROM_ROW_COL(row, col) ((row * BOARD_SIZE) + col+1) //Adding +1 since, choice is 1 index based

////////////////////////////////////////////////////////////////////////////////////////
/**
* Win: If the player has two in a row, they can place a third to get three in a row.
* Block: If the opponent has two in a row, the player must play the third themself to block the opponent.
* Fork: Create an opportunity where the player has two threats to win (two non-blocked lines of 2).
* Blocking an opponent's fork:
* Option 1: The player should create two in a row to force the opponent into defending, as long as it 
    doesn't result in them creating a fork. For example, if "X" has a corner, "O" has the center, and "X"
    has the opposite corner as well, "O" must not play a corner in order to win. (Playing a corner in this
    scenario creates a fork for "X" to win.)
*
* Option 2: If there is a configuration where the opponent can fork, the player should block that fork.
* Center: A player marks the center. (If it is the first move of the game, playing on a corner gives "O" more opportunities to make a mistake and may therefore be the better choice; however, it makes no difference between perfect players.)
* Opposite corner: If the opponent is in the corner, the player plays the opposite corner.
* Empty corner: The player plays in a corner square.
* Empty side: The player plays in a middle square on any of the 4 sides.
**/
////////////////////////////////////////////////////////////////////////////////////////


int Computer::getChoice()
{
    //Computer turn should never be invalid, lets see
    int iChoice = INVALID_INPUT;
    
    iChoice = tryWin();     if(SUCCESS(iChoice)) { return iChoice; }
    iChoice = tryBlock();   if(SUCCESS(iChoice)) { return iChoice; }
    iChoice = tryFork();    if(SUCCESS(iChoice)) { return iChoice; }
    iChoice = tryCenter();  if(SUCCESS(iChoice)) { return iChoice; }
    iChoice = tryCorner();  if(SUCCESS(iChoice)) { return iChoice; }
    iChoice = trySide();    if(SUCCESS(iChoice)) { return iChoice; }
    
    return iChoice;
}

int Computer::tryWin()
{
    int iChoice = INVALID_INPUT;
    
    iChoice = tryWinRow();          if(SUCCESS(iChoice)) { return iChoice; }
    iChoice = tryWinColumn();       if(SUCCESS(iChoice)) { return iChoice; }
    iChoice = tryWinDiagonally();   if(SUCCESS(iChoice)) { return iChoice; }
    
    return iChoice;
}

int Computer::getOpponenetsPositionCountInRow(int iRow, int *iFirstEmptyPos/*out value*/)
{
    *iFirstEmptyPos = INVALID_INPUT;
    int iPositions = 0;
    
    const TicTacToeGame *pGame = getGame();
    
    for (int iCol=0; iCol<BOARD_SIZE; ++iCol)
    {
        if (pGame->getBoardElement(iRow, iCol) != getSign() && pGame->getBoardElement(iRow, iCol) != EMPTY) { ++iPositions; }
        else if(!SUCCESS(*iFirstEmptyPos) && pGame->getBoardElement(iRow, iCol) == EMPTY) { *iFirstEmptyPos = CHOICE_FROM_ROW_COL(iRow, iCol); }
    }
    
    return iPositions;
}

int Computer::getOpponenetsPositionCountInCol(int iCol, int *iFirstEmptyPos/*out value*/)
{
    *iFirstEmptyPos = INVALID_INPUT;
    int iPositions = 0;
    
    const TicTacToeGame *pGame = getGame();
    
    for (int iRow=0; iRow<BOARD_SIZE; ++iRow)
    {
        if (pGame->getBoardElement(iRow, iCol) != getSign() && pGame->getBoardElement(iRow, iCol) != EMPTY) { ++iPositions; }
        else if(!SUCCESS(*iFirstEmptyPos)  && pGame->getBoardElement(iRow, iCol) == EMPTY) { *iFirstEmptyPos = CHOICE_FROM_ROW_COL(iRow, iCol); }
    }
    
    return iPositions;
}


int Computer::tryWinRow()
{
    int iRowNumber = INVALID_INPUT;
    int iChoice = INVALID_INPUT;
    const TicTacToeGame *pGame = getGame();
    BoardValueType ** pBoard = pGame->getBoard();
    
    for (int i=0; i<BOARD_SIZE; ++i)
    {
        int iPositions = 0;
        iChoice = INVALID_INPUT;
        for (int j=0; j<BOARD_SIZE; ++j)
        {
            if (pBoard[i][j] == getSign()) { ++iPositions; }
            else if(!SUCCESS(iChoice) && pGame->getBoardElement(i, j) == EMPTY){ iChoice = CHOICE_FROM_ROW_COL(i, j); }
        }
        
        if (iPositions == (BOARD_SIZE - 1))
        {
            iRowNumber = i;
            break;
        }
    }
    
    //If we find valid row then only return iChoice otherwise return Invalid
    return SUCCESS(iRowNumber) ? iChoice : INVALID_INPUT;
}

int Computer::tryWinColumn()
{
    int iColNumber = INVALID_INPUT;
    int iChoice = INVALID_INPUT;
    const TicTacToeGame *pGame = getGame();
    BoardValueType ** pBoard = pGame->getBoard();
    
    for (int i=0; i<BOARD_SIZE; ++i)
    {
        int iPositions = 0;
        iChoice = INVALID_INPUT;
        for (int j=0; j<BOARD_SIZE; ++j)
        {
            if (pBoard[j][i] == getSign()) { ++iPositions; }
            else if(!SUCCESS(iChoice) && pGame->getBoardElement(j, i) == EMPTY){ iChoice = CHOICE_FROM_ROW_COL(j, i); } //Make note of empty box, it will require when we will find this row,col can be won
        }
        
        if (iPositions == (BOARD_SIZE - 1))
        {
            iColNumber = i;
            break;
        }
    }
    
    //If we find valid row then only return iChoice otherwise return Invalid
    return SUCCESS(iColNumber) ? iChoice : INVALID_INPUT;
}

int Computer::tryWinDiagonally()
{
    int iChoice = INVALID_INPUT;
    const TicTacToeGame *pGame = getGame();

    int iPositions = 0;
    for (int i=0; i<BOARD_SIZE; ++i)
    {
        if (pGame->getBoardElement(i, i) == getSign()) { ++iPositions; }
        else if(!SUCCESS(iChoice) && pGame->getBoardElement(i, i) == EMPTY) { iChoice = CHOICE_FROM_ROW_COL(i, i); }
    }
    
    //If can't win first diagonal then check another
    if (iPositions != (BOARD_SIZE - 1))
    {
        int iRow = 0;
        int iCol = BOARD_SIZE - 1;
        iPositions = 0;
        iChoice = INVALID_INPUT;
        for (int i=0; i<BOARD_SIZE; ++i)
        {
            BoardValueType value = pGame->getBoardElement(iRow++, iCol--);
            if (value == getSign()) { ++iPositions; }
            else if(!SUCCESS(iChoice) && value == EMPTY){ iChoice = CHOICE_FROM_ROW_COL(iRow-1, iCol-1); }
        }
    }
    
    return iPositions == (BOARD_SIZE - 1) ? iChoice : INVALID_INPUT;
}



int Computer::tryBlock()
{
    const TicTacToeGame *pGame = getGame();
    bool bCenterIsEmpty = (pGame->getCenterValue() == EMPTY);
    bool bOpponentHasBothDiagonalCorner =
    (pGame->getTopLeftCornerValue() == pGame->getBottomRightCornerValue() && pGame->getTopLeftCornerValue() != getSign() && pGame->getTopLeftCornerValue() != EMPTY) ||
    (pGame->getTopRightCornerValue() == pGame->getBottomLeftCornerValue() && pGame->getTopRightCornerValue() != getSign() && pGame->getTopRightCornerValue() != EMPTY);
    
    int iChoice = INVALID_INPUT;
    
    //Diagonal block
    if (bCenterIsEmpty)
    {
        if (bOpponentHasBothDiagonalCorner)
        {
            iChoice = pGame->getCenterPosition();
        }
    }
    
    if (!SUCCESS(iChoice))//Row or Column Block
    {
        for (int iRow=0; iRow<BOARD_SIZE; ++iRow)
        {
            int iFirstEmptyPos = INVALID_INPUT;
            int iPositionCount = getOpponenetsPositionCountInRow(iRow, &iFirstEmptyPos);
            
            if(iPositionCount == (BOARD_SIZE - 1) && SUCCESS(iFirstEmptyPos))
            {
                iChoice = iFirstEmptyPos;
                break;
            }
        }
    }
    
    if (!SUCCESS(iChoice))
    {
        for (int iCol=0; iCol<BOARD_SIZE; ++iCol)
        {
            int iFirstEmptyPos = INVALID_INPUT;
            int iPositionCount = getOpponenetsPositionCountInCol(iCol, &iFirstEmptyPos);
            
            if(iPositionCount == (BOARD_SIZE - 1) && SUCCESS(iFirstEmptyPos))
            {
                iChoice = iFirstEmptyPos;
                break;
            }
        }
    }
    
    return iChoice;
}

int Computer::tryFork()
{
    return INVALID_INPUT; //TODO
}

int Computer::tryCenter()
{
    if (getGame()->getCenterValue() == EMPTY)
    {
        return getGame()->getCenterPosition();
    }
    
    return INVALID_INPUT;
}

int Computer::tryCorner()
{
    int iChoice = INVALID_INPUT;
    if (getGame()->getTopLeftCornerValue() == EMPTY)
    {
        iChoice = getGame()->getTopLeftCornerPosition();
    }
    else if(getGame()->getTopRightCornerValue() == EMPTY)
    {
        iChoice = getGame()->getTopRightCornerPosition();
    }
    else if(getGame()->getBottomLeftCornerValue() == EMPTY)
    {
        iChoice = getGame()->getBottomLeftCornerPosition();
    }
    else if(getGame()->getBottomRightCornerValue() == EMPTY)
    {
        iChoice = getGame()->getBottomRightCornerPosition();
    }
    
    return iChoice;
}

int Computer::trySide()
{
    int iChoice = INVALID_INPUT;
    if (getGame()->getMiddleLeftSideValue() == EMPTY)
    {
        iChoice = getGame()->getMiddleLeftSidePosition();
    }
    else if (getGame()->getMiddleRightSideValue() == EMPTY)
    {
        iChoice = getGame()->getMiddleRightSidePosition();
    }
    else if (getGame()->getMiddleTopSideValue() == EMPTY)
    {
        iChoice = getGame()->getMiddleTopSidePosition();
    }
    else if (getGame()->getMiddleBottomSideValue() == EMPTY)
    {
        iChoice = getGame()->getMiddleBottomSidePosition();
    }
    
    return iChoice;
}

