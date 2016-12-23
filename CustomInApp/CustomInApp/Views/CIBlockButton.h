//
//  CIBlockButton.h
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^ActionBlock)();

@interface CIBlockButton : UIButton

@property (nonatomic, copy) ActionBlock actionBlock;

- (void)handleTouchUpInsideEventWithBlock:(ActionBlock)action;

@end
