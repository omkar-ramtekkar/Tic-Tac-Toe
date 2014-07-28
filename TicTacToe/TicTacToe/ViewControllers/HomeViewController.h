//
//  HomeViewController.h
//  TicTacToe
//
//  Created by Om on 30/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface HomeViewController : UIViewController

@property (weak, nonatomic) IBOutlet UILabel *ticLabel;
@property (weak, nonatomic) IBOutlet UILabel *tacLabel;
@property (weak, nonatomic) IBOutlet UILabel *toeLabel;

@property (weak, nonatomic) IBOutlet UIButton *onePlayerButton;
@property (weak, nonatomic) IBOutlet UIButton *twoPlayerButton;
@property (weak, nonatomic) IBOutlet UIButton *optionButton;

- (IBAction)onePlayerAction:(id)sender;
- (IBAction)twoPlayerAction:(id)sender;
- (IBAction)optionsAction:(id)sender;

@end
