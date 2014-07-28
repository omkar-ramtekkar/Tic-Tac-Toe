//
//  GameSettingModel.m
//  TicTacToe
//
//  Created by Om on 01/02/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import "GameSettingModel.h"

static GameSettingModel *settingModel = nil;

@interface GameSettingModel()

@property(nonatomic) UIFont *appDefaultFont;
-(void) initialize;
@end

@implementation GameSettingModel

@synthesize soundEnable;
@synthesize difficultyLevel;
@synthesize gameMode;
@synthesize player1Name;
@synthesize player2Name;
@synthesize player1Image;
@synthesize player2Image;
@synthesize appDefaultFont;

-(id) init
{
    self = [super init];
    [self initialize];
    
    return self;
}

//For now setting is hardcoaded, but it can be stored in coredata and retrive.
-(void) initialize
{
    self.soundEnable = YES;
    self.difficultyLevel = Hard;
    self.gameMode = OnePlayer;
    self.player1Name = @"Omkar";
    self.player2Name = @"Super User";
    self.player1Image = [UIImage imageNamed:@"RedSign.png"];
    self.player2Image = [UIImage imageNamed:@"BlueSign.png"];
    self.appDefaultFont = [UIFont fontWithName:@"KBDunkTank" size:18.0f];
}

@end
