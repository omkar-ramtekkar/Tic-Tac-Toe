//
//  PlayViewController.h
//  TicTacToe
//
//  Created by Om on 01/02/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#import <UIKit/UIKit.h>



@interface PlayViewController : UIViewController<UIAlertViewDelegate>
{
    
}
@property (weak, nonatomic) IBOutlet UIButton *button1;
@property (weak, nonatomic) IBOutlet UIButton *button2;
@property (weak, nonatomic) IBOutlet UIButton *button3;
@property (weak, nonatomic) IBOutlet UIButton *button4;
@property (weak, nonatomic) IBOutlet UIButton *button5;
@property (weak, nonatomic) IBOutlet UIButton *button6;
@property (weak, nonatomic) IBOutlet UIButton *button7;
@property (weak, nonatomic) IBOutlet UIButton *button8;
@property (weak, nonatomic) IBOutlet UIButton *button9;

@property (weak, nonatomic) IBOutlet UIImageView *player1Sign;
@property (weak, nonatomic) IBOutlet UIImageView *player2Sign;
@property (weak, nonatomic) IBOutlet UILabel *player1Status;
@property (weak, nonatomic) IBOutlet UILabel *player2Status;

-(IBAction)replayButtonAction :(id)sender;

@end
