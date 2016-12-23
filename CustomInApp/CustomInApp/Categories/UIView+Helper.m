//
//  UIView+Helper.m
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "UIView+Helper.h"

@implementation UIView (Helper)

+ (UIView *)ci_viewFromNib:(NSString *)nibName {
    
    NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:nibName owner:nil options:nil];
    
    // Find a view inside the nib file
    for (id view in topLevelObjects) {
        if([view isKindOfClass:[UIView class]])  {
            return view;
        }
    }
    
    return nil;
}

@end
