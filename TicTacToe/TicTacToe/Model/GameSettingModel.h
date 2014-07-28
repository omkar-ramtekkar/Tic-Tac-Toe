//
//  GameSettingModel.h
//  TicTacToe
//
//  Created by Om on 01/02/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum
{
    Easy = 0,
    Medium,
    Hard
}GameDifficultyLevel;

typedef enum
{
    OnePlayer = 1,
    TwoPlayer = 2,
}GameMode;

@interface GameSettingModel : NSObject

@property (nonatomic, assign)   BOOL                soundEnable;
@property (nonatomic, assign)   GameDifficultyLevel difficultyLevel;
@property (nonatomic, copy)     NSString            *player1Name;
@property (nonatomic, copy)     NSString            *player2Name;
@property (nonatomic, assign)   GameMode            gameMode;
@property (nonatomic, retain)   UIImage             *player1Image;
@property (nonatomic, retain)   UIImage             *player2Image;
@property (nonatomic, readonly) UIFont              *appDefaultFont;

@end
