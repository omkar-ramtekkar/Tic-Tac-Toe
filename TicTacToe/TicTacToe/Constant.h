//
//  Constant.h
//  TicTacToe
//
//  Created by Om on 01/02/14.
//  Copyright (c) 2014 ThoughtWorks. All rights reserved.
//

#ifndef TicTacToe_Constant_h
#define TicTacToe_Constant_h

#include "Settings.h"

#define SUCCESS(value)  ((value) != INVALID_INPUT)
#define FAILED(value)   (!SUCCESS(value))

#define assert(...) //assert(...)

#define VALIDATE_POINTER(pointer, msg) if(!pointer) { NSLog(msg); @throw msg; }


#define kNotificationGameOver           @"kNotificationGameOver"
#define kNotificationGameStarted        @"kNotificationGameStarted"
#define kNotificationGameDrawn          @"kNotificationGameDrawn"
#define kNotificationGameBoardUpdated   @"kNotificationGameBoardUpdated"


///////// Notification User Info Keys ////////////
#define kNotificationUserInfoKeyPlayerID        @"kNotificationUserInfoKeyPlayerID"
#define kNotificationUserInfoKeyPlayerChoice    @"kNotificationUserInfoKeyPlayerChoice"

#endif
