//
//  TicTacToeGameManager.m
//  TicTacToe
//
//  Created by Om on 01/02/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import "TicTacToeGameManager.h"
#import "GameSettingModel.h"
#include "UserInputContext.h"
#include "TicTacToeGame.h"

#define VALIDATE_INPUT_CONTEXT(pointer) VALIDATE_POINTER(pointer, @"UserInputContext is NULL")
#define VALIDATE_TIC_TAC_TOE_GAME(pointer) VALIDATE_POINTER(pointer, @"TicTacToeGame Object is NULL")

static TicTacToeGameManager *gameManager_g = nil;


@interface TicTacToeGameManager()

@property (nonatomic) GameSettingModel *settingModel;
@property (nonatomic) PlayerID currentPlayerTurn;
@property (nonatomic) PlayerID lastPlayerWon;
@property (nonatomic) NSUInteger player1WinningCount;
@property (nonatomic) NSUInteger player2WinningCount;
@property(nonatomic, retain) NSRecursiveLock *turnLock;

-(void) initializeGameSettings;
-(void) initializeGameAndUserContext;

@end


@implementation TicTacToeGameManager

@synthesize settingModel;
@synthesize currentPlayerTurn;
@synthesize lastPlayerWon;
@synthesize turnLock;
@synthesize player1WinningCount;
@synthesize player2WinningCount;
@dynamic lastUserChoice;

+(TicTacToeGameManager*) defaultGameManager
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        gameManager_g = [[TicTacToeGameManager alloc] init];
        [gameManager_g initialize];
    });
    
    return gameManager_g;
}

+(void) postNotification:(NSNotification*) note
{
    [[NSNotificationCenter defaultCenter] performSelectorOnMainThread:@selector(postNotification:) withObject:note waitUntilDone:NO];
}

-(void) initialize
{
    self.turnLock = [[NSRecursiveLock alloc] init];
    self.lastPlayerWon = Player1; //Always set to user1
    self.currentPlayerTurn = self.lastPlayerWon;
    
    [self initializeGameSettings];
    [self initializeGameAndUserContext];
}

-(void) initializeGameSettings
{
    self.settingModel = [[GameSettingModel alloc] init];
}

-(void) initializeGameAndUserContext
{
    _pInputContext = new UserInputContext();
}

-(NSUInteger) lastUserChoice
{
    VALIDATE_INPUT_CONTEXT(_pInputContext);
    
    NSUInteger lastUserChoice = 0;
    
    if (_pInputContext)
    {
        lastUserChoice = _pInputContext->getChoice();
    }
    
    return lastUserChoice;
}

-(void) setLastUserChoice:(NSUInteger)lastUserChoice
{
    VALIDATE_INPUT_CONTEXT(_pInputContext);
    
    if (_pInputContext)
    {
        _pInputContext->setLastUserChoice((int)lastUserChoice);
    }
}

-(void) startNewGame
{
    delete _pTicTacToeGame;
    
    if (self.settingModel.gameMode == OnePlayer)
    {
        _pTicTacToeGame = TicTacToeGame::gameWithOnePlayer();
    }
    else
    {
        _pTicTacToeGame = TicTacToeGame::gameWithTwoPlayer();
    }
    
    VALIDATE_TIC_TAC_TOE_GAME(_pTicTacToeGame);
    
    _pTicTacToeGame->setUserInputContext(_pInputContext);
    _pTicTacToeGame->startNewGame();
    
    if (self.lastPlayerWon == Player2) //If last time computer has won then on restart play the first turn
    {
        [self performSelector:@selector(playTurn) withObject:nil afterDelay:0.5];
    }
}

-(void) endGame
{
    VALIDATE_TIC_TAC_TOE_GAME(_pTicTacToeGame);
    
    if (_pTicTacToeGame)
    {
        _pTicTacToeGame->endGame();
    }
}

-(void) restartGame
{
    VALIDATE_TIC_TAC_TOE_GAME(_pTicTacToeGame);
    
    if (_pTicTacToeGame)
    {
        _pTicTacToeGame->restartGame();
        
        if (self.lastPlayerWon == Player2) //If last time computer has won then on restart play the first turn
        {
            [self performSelector:@selector(playTurn) withObject:nil afterDelay:0.5];
        }
    }
}

-(void) undoLastChoice
{
    //TODO : Not Implemented
    @throw @"Feature not implemented";
}

-(BOOL) playTurn:(NSUInteger) choice
{
    BOOL bPlayedTurn = NO;
    @try
    {
        VALIDATE_INPUT_CONTEXT(_pInputContext);
        VALIDATE_TIC_TAC_TOE_GAME(_pTicTacToeGame);
        
        _pInputContext->setLastUserChoice((int)choice);
        
        if (self.settingModel.gameMode == OnePlayer)
        {
            //When game is in single mode, after user play Computer will play automatically after 0.5 sec
            assert(self.currentPlayerTurn == Player1); //Something is wrong with player id, it should be user's id
            bPlayedTurn = [self playTurn];
            [self performSelector:@selector(playTurn) withObject:Nil afterDelay:0.5];
        }
        else if(self.settingModel.gameMode == TwoPlayer)
        {
            bPlayedTurn = [self playTurn];
        }
    }
    @catch (NSException *exception)
    {
        NSLog(@"Exception : %@",exception);
    }
    
    return bPlayedTurn;
}

-(BOOL) playTurn
{
    BOOL bPlayedTurn = NO;
    @try
    {
        VALIDATE_TIC_TAC_TOE_GAME(_pTicTacToeGame)
        
        if ([self.turnLock tryLock] && !_pTicTacToeGame->isGameOver() && !_pTicTacToeGame->isGameDrawn())
        {
            [self.turnLock lock];
            
            int iPlayerChoice = INVALID_INPUT;
            bPlayedTurn = SUCCESS(iPlayerChoice = _pTicTacToeGame->playTurn(self.currentPlayerTurn));
            
            NSDictionary *playerInfo = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithUnsignedInteger:self.currentPlayerTurn], kNotificationUserInfoKeyPlayerID,
                                        [NSNumber numberWithInt:iPlayerChoice], kNotificationUserInfoKeyPlayerChoice, nil];
            
            if (bPlayedTurn)
            {
                [TicTacToeGameManager postNotification:[NSNotification notificationWithName:kNotificationGameBoardUpdated object:self userInfo:playerInfo]];

            }
            
            if (_pTicTacToeGame->isGameOver())
            {
                if (self.currentPlayerTurn == Player1)
                {
                    ++self.player1WinningCount;
                }
                else
                {
                    ++self.player2WinningCount;
                }
                
                NSLog(@"*** Player(%i) Won the Game **** ", self.currentPlayerTurn);
                self.lastPlayerWon = self.currentPlayerTurn;
                [TicTacToeGameManager postNotification:[NSNotification notificationWithName:kNotificationGameOver object:self userInfo:playerInfo]];
            }
            else if (_pTicTacToeGame->isGameDrawn())
            {
                NSLog(@"*** Game Drawn **** ");
                [TicTacToeGameManager postNotification:[NSNotification notificationWithName:kNotificationGameDrawn object:self userInfo:nil]];
            }
            else if(bPlayedTurn)
            {
                self.currentPlayerTurn = self.currentPlayerTurn == Player1 ? Player2 : Player1;
            }
        }
        else
        {
            //Note - Only for debug purpose
            if(![self.turnLock tryLock]){ NSLog(@"Player failed to play as other player(%i) is currently playing", self.currentPlayerTurn); }
            
            if (_pTicTacToeGame->isGameOver()){ NSLog(@"*** Player(%i) Won the Game **** ", self.currentPlayerTurn); }
        }
    }
    @catch (NSException *exception)
    {
        //Re-through the exception
        NSLog(@"Exception : %@",exception);
        @throw exception;
    }
    @catch (...)
    {
        NSLog(@"Exception : Unknown");
    }
    @finally
    {
        [self.turnLock unlock];
    }
    
    return bPlayedTurn;
}

@end
