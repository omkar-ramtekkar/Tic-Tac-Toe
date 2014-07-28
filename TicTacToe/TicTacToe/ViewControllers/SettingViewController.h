//
//  SettingViewController.h
//  TicTacToe
//
//  Created by Om on 30/01/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SettingViewController : UIViewController<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UIImageView *player1Sign;
@property (weak, nonatomic) IBOutlet UIImageView *player2Sign;
@property (weak, nonatomic) IBOutlet UITextField *player1NameTxtField;
@property (weak, nonatomic) IBOutlet UITextField *player2NameTxtField;
@property (weak, nonatomic) IBOutlet UILabel *player1NameLabel;
@property (weak, nonatomic) IBOutlet UILabel *player2NameLabel;
@property (weak, nonatomic) IBOutlet UILabel *playerSign1Label;
@property (weak, nonatomic) IBOutlet UILabel *playerSign2Label;
@property (weak, nonatomic) IBOutlet UIButton *sign1;
@property (weak, nonatomic) IBOutlet UIButton *sign2;
@property (weak, nonatomic) IBOutlet UIButton *sign3;
@property (weak, nonatomic) IBOutlet UIButton *sign4;
@property (weak, nonatomic) IBOutlet UIButton *playButton;

-(IBAction)playButtonAction:(id)sender;
-(IBAction)player1SignAction:(id)sender;
-(IBAction)player2SignAction:(id)sender;

@end
