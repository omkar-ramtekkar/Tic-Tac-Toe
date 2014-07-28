    //
//  HomeViewController.m
//  TicTacToe
//
//  Created by Om on 30/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import "HomeViewController.h"
#import "SettingViewController.h"
#import "TicTacToeGameManager.h"
#import "GameSettingModel.h"
#import "PlayViewController.h"

@interface HomeViewController ()

@end

@implementation HomeViewController

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
    [self.navigationController setNavigationBarHidden:YES];
    UIFont *uiFont = [[[[TicTacToeGameManager defaultGameManager] settingModel] appDefaultFont] fontWithSize:24];
    
    
    [[UINavigationBar appearance] setTitleTextAttributes: @{
                                                            UITextAttributeTextColor: [UIColor magentaColor],
                                                            UITextAttributeTextShadowOffset: [NSValue valueWithUIOffset:UIOffsetMake(0.0f, 1.0f)],
                                                            UITextAttributeFont: [uiFont fontWithSize:24]
                                                            }];
    
    self.title = NSLocalizedString(@"Home", nil);
    
    self.ticLabel.font = [uiFont fontWithSize:36];
    self.tacLabel.font = [uiFont fontWithSize:36];
    self.toeLabel.font = [uiFont fontWithSize:36];
    
    
    self.onePlayerButton.titleLabel.font = uiFont;
    self.twoPlayerButton.titleLabel.font = uiFont;
    self.optionButton.titleLabel.font = uiFont;
    
    // Do any additional setup after loading the view from its nib.
}

-(void) viewWillAppear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction) onePlayerAction:(id)sender
{
    [[[TicTacToeGameManager defaultGameManager] settingModel] setGameMode:OnePlayer];
    
    PlayViewController *playViewController = [[PlayViewController alloc] initWithNibName:@"PlayViewController" bundle:nil];
    
    [self.navigationController pushViewController:playViewController animated:YES];
}

- (IBAction) twoPlayerAction:(id)sender
{
    [[[TicTacToeGameManager defaultGameManager] settingModel] setGameMode:TwoPlayer];
    
    PlayViewController *playViewController = [[PlayViewController alloc] initWithNibName:@"PlayViewController" bundle:nil];
    
    [self.navigationController pushViewController:playViewController animated:YES];
}

- (IBAction)optionsAction:(id)sender
{
    SettingViewController *settingViewController = [[SettingViewController alloc] initWithNibName:@"SettingViewController" bundle:nil];
    [self.navigationController pushViewController:settingViewController animated:YES];
}

@end
