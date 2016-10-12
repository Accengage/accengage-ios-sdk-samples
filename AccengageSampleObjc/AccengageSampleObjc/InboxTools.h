//
//  InboxTools.h
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define BLUE_COLOR [UIColor colorWithRed:0/255.0 green:121.0/255.0 blue:255.0/255.0 alpha:1.0]

@interface InboxTools : NSObject

+ (UIColor*) colorForCategory:(NSString*)category;
+ (NSString*) labelTextForDate:(NSDate*)date;
@end
