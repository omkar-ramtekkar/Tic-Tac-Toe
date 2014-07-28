//
//  SettingViewController.m
//  TicTacToe
//
//  Created by Om on 30/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import "SettingViewController.h"
#import "TicTacToeGameManager.h"
#import "PlayViewController.h"
#import "GameSettingModel.h"

@interface SettingViewController ()
@end


@implementation SettingViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [self initializeSettings];
    self.title = NSLocalizedString(@"Options", nil);
    [self.navigationController setNavigationBarHidden:NO];
    self.navigationItem.title = self.title;
    
    [super viewDidLoad];
}

-(void) viewDidDisappear:(BOOL)animated
{
    [self saveSettings];
    [super viewDidDisappear:animated];
}

-(void) initializeSettings
{
    TicTacToeGameManager *manager = [TicTacToeGameManager defaultGameManager];
    self.player1Sign.image = manager.settingModel.player1Image;
    self.player2Sign.image = manager.settingModel.player2Image;
    
    
    UIFont *settingFont = [manager.settingModel.appDefaultFont fontWithSize:16];
    
    self.player1NameTxtField.font = [settingFont fontWithSize:12];
    self.player2NameTxtField.font = [settingFont fontWithSize:12];
    
    self.player1NameTxtField.delegate = self;
    self.player2NameTxtField.delegate = self;
    
    self.player1NameTxtField.text = manager.settingModel.player1Name;
    self.player2NameTxtField.text = manager.settingModel.player2Name;
    
    self.player1NameLabel.font = settingFont;
    self.player2NameLabel.font = settingFont;
    
    self.playerSign1Label.font = [settingFont fontWithSize:20];
    self.playerSign2Label.font = [settingFont fontWithSize:20];
    
    self.playButton.titleLabel.font = [settingFont fontWithSize:28];
    self.playButton.layer.borderColor = self.playButton.titleLabel.textColor.CGColor;
    self.playButton.layer.cornerRadius = 7;
    self.playButton.layer.borderWidth = 5.0f;
    
    [self.sign1 setBackgroundImage:[UIImage imageNamed:@"RedSign.png"] forState:UIControlStateNormal];
    [self.sign2 setBackgroundImage:[UIImage imageNamed:@"GreenSign.png"] forState:UIControlStateNormal];
    [self.sign3 setBackgroundImage:[UIImage imageNamed:@"PinkSign.png"] forState:UIControlStateNormal];
    [self.sign4 setBackgroundImage:[UIImage imageNamed:@"BlueSign.png"] forState:UIControlStateNormal];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return NO;
}

-(void) saveSettings
{
    GameSettingModel *gameSetting = [[TicTacToeGameManager defaultGameManager] settingModel];
    
    gameSetting.player1Name = self.player1NameTxtField.text;
    gameSetting.player2Name = self.player2NameTxtField.text;
    
    gameSetting.player1Image = self.player1Sign.image;
    
    gameSetting.player2Image = self.player2Sign.image;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)playButtonAction:(id)sender
{
    PlayViewController *playViewController = [[PlayViewController alloc] initWithNibName:@"PlayViewController" bundle:nil];
    
    [self.navigationController pushViewController:playViewController animated:YES];
}

-(IBAction)player1SignAction:(id)sender
{
    if ([sender respondsToSelector:@selector(backgroundImageForState:)])
    {
        [[[TicTacToeGameManager defaultGameManager] settingModel] setPlayer1Image:[sender backgroundImageForState:UIControlStateNormal]];
        self.player1Sign.image = [sender backgroundImageForState:UIControlStateNormal];
    }
}

-(IBAction)player2SignAction:(id)sender
{
    if ([sender respondsToSelector:@selector(backgroundImageForState:)])
    {
        [[[TicTacToeGameManager defaultGameManager] settingModel] setPlayer2Image:[sender backgroundImageForState:UIControlStateNormal]];
        self.player2Sign.image = [sender backgroundImageForState:UIControlStateNormal];
    }
}

@end
