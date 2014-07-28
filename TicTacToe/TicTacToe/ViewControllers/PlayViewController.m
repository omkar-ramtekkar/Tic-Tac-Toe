//
//  PlayViewController.m
//  TicTacToe
//
//  Created by Om on 01/02/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import "PlayViewController.h"
#import "TicTacToeGameManager.h"
#import "GameSettingModel.h"

@interface PlayViewController ()

@property(nonatomic, retain) NSArray *slots;

@end

@implementation PlayViewController

@synthesize slots;

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
    [super viewDidLoad];
    
    self.title = NSLocalizedString(@"Game Board", nil);
    [self.navigationController setNavigationBarHidden:NO];
    self.navigationItem.title = self.title;
    
    [self registerNotifications];
    
    self.slots = [NSArray arrayWithObjects:self.button1, self.button2, self.button3, self.button4, self.button5, self.button6, self.button7, self.button8, self.button9, nil];
    
    TicTacToeGameManager *manager = [TicTacToeGameManager defaultGameManager];
    self.player1Status.font = [manager.settingModel.appDefaultFont fontWithSize:16];
    self.player2Status.font = [manager.settingModel.appDefaultFont fontWithSize:16];
    
    [self updatePlayerStatusAndDetails];
    
    [[TicTacToeGameManager defaultGameManager] startNewGame];
}

-(void) registerNotifications
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(boardUpdated:) name:kNotificationGameBoardUpdated object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(gameOver:) name:kNotificationGameOver object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(resetBoardAndUpdatePlayerDetails:) name:kNotificationGameStarted object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(gameDrawn:) name:kNotificationGameDrawn object:nil];
}

-(void) updatePlayerStatusAndDetails
{
    TicTacToeGameManager *manager = [TicTacToeGameManager defaultGameManager];
    self.player1Sign.image = [[manager settingModel] player1Image];
    self.player2Sign.image = [[manager settingModel] player2Image];
    
    self.player1Status.text = [NSString stringWithFormat:@"%@ : %lu",manager.settingModel.player1Name, (unsigned long)manager.player1WinningCount];
    self.player2Status.text = [NSString stringWithFormat:@"%@ : %lu",manager.settingModel.player2Name, (unsigned long)manager.player2WinningCount];
}

-(void) gameOver:(NSNotification*) note
{
    [self updatePlayerStatusAndDetails];
    
    NSString *playerName = [[[TicTacToeGameManager defaultGameManager] settingModel] player1Name];

    if ([[[note userInfo] objectForKey:kNotificationUserInfoKeyPlayerID] intValue] == Player2)
    {
        playerName = [[[TicTacToeGameManager defaultGameManager] settingModel] player2Name];
    }
    
    NSString *msg = [NSString stringWithFormat:@"%@ Won", playerName];
    
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Game Over", nil) message:msg delegate:self cancelButtonTitle: NSLocalizedString(@"No", nil) otherButtonTitles:NSLocalizedString(@"Replay", nil), nil];
    
    alertView.delegate = self;
    [alertView show];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1)
    {
        [self resetBoardAndUpdatePlayerDetails:nil];
    }
}

-(void) resetBoardAndUpdatePlayerDetails:(NSNotification*) note
{
    [[TicTacToeGameManager defaultGameManager] restartGame];
    [self updatePlayerStatusAndDetails];
    
    for (UIButton *slot in self.slots)
    {
        [slot setBackgroundImage:nil forState:UIControlStateNormal];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) userSelectionAction:(id) sender
{
    //Validate the sender
    if ([sender isKindOfClass:[UIButton class]])
    {
        [[TicTacToeGameManager defaultGameManager] playTurn:[sender tag]];
    }
}

-(void) boardUpdated:(NSNotification*) note
{
    UIImage *image = [[[TicTacToeGameManager defaultGameManager] settingModel] player1Image];
    
    if ([[[note userInfo] objectForKey:kNotificationUserInfoKeyPlayerID] intValue] == Player2)
    {
        image = [[[TicTacToeGameManager defaultGameManager] settingModel] player2Image];
    }

    id sender = [self.slots objectAtIndex:[[[note userInfo] objectForKey:kNotificationUserInfoKeyPlayerChoice] intValue] - 1];
    
    [sender setBackgroundImage:image forState:UIControlStateNormal];
}

-(void) gameDrawn:(NSNotification*) note
{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Game Drawn", nil) message:nil delegate:self cancelButtonTitle: NSLocalizedString(@"No", nil) otherButtonTitles:NSLocalizedString(@"Replay", nil), nil];
    
    alertView.delegate = self;
    [alertView show];
}

-(IBAction)replayButtonAction :(id)sender
{
    [self resetBoardAndUpdatePlayerDetails:nil];
}

@end
