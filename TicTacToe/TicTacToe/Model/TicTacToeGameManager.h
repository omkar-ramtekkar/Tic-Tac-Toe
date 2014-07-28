//
//  TicTacToeGameManager.h
//  TicTacToe
//
//  Created by Om on 01/02/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "TicTacToeGame.h"
class UserInputContext;


@class GameSettingModel;

@interface TicTacToeGameManager : NSObject
{
    UserInputContext *_pInputContext;
    TicTacToeGame *_pTicTacToeGame;
}

@property (nonatomic, assign) NSUInteger lastUserChoice;
@property (nonatomic, readonly) GameSettingModel *settingModel;
@property (nonatomic, readonly) PlayerID currentPlayerTurn;
@property (nonatomic, readonly) PlayerID lastPlayerWon;
@property (nonatomic, readonly) NSUInteger player1WinningCount;
@property (nonatomic, readonly) NSUInteger player2WinningCount;


+(TicTacToeGameManager*) defaultGameManager;
+(void) postNotification:(NSNotification*) note;

-(void) startNewGame;
-(void) endGame;
-(void) restartGame;
-(void) undoLastChoice;

-(BOOL) playTurn:(NSUInteger) choice;


@end
