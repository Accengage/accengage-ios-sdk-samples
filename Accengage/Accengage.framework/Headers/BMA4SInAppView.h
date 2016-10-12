//
//  BMA4SInAppView.h
//  BMA4SSDK
//
//  Created by Yassir BARCHI on 03/08/2015.
//  Copyright (c) 2015 Accengage. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BMA4SInAppView : UIView

/**
 * By default the SDK autosize the inApp view. Set the value to YES if you 
 * don't want that the SDK autosize the inApp view and keeps the original 
 * bounds. 
 */
@property (nonatomic, assign) IBInspectable BOOL autosizingDisabled;

@end
