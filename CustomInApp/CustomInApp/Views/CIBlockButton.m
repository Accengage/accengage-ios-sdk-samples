//
//  CIBlockButton.m
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "CIBlockButton.h"

@implementation CIBlockButton

- (instancetype)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    
    if (self) {
        [self addTarget:self action:@selector(callActionBlock:) forControlEvents:UIControlEventTouchUpInside];
    }
    return self;
}

- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder {
    
    self = [super initWithCoder:aDecoder];
    
    if (self) {
        [self addTarget:self action:@selector(callActionBlock:) forControlEvents:UIControlEventTouchUpInside];
    }
    
    return self;
}


- (void)handleTouchUpInsideEventWithBlock:(ActionBlock)action {
    self.actionBlock = action;
}

- (void)callActionBlock:(id)sender{
    if (self.actionBlock) {
        self.actionBlock();
    }
}

@end
