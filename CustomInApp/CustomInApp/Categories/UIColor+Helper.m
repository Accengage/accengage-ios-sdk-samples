//
//  UIColor+Helper.m
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "UIColor+Helper.h"

@implementation UIColor (Helper)

+ (instancetype)ci_colorWithCSS:(NSString *)string {
    if (!string) {
        return nil;
    }
    
    //convert to lowercase
    string = [string lowercaseString];
    
    //try hex
    string = [string stringByReplacingOccurrencesOfString:@"#" withString:@""];
    string = [string stringByReplacingOccurrencesOfString:@"0x" withString:@""];
    
    switch ([string length]) {
        case 0: {
            string = @"00000000";
            break;
        }
        case 3: {
            NSString *red = [string substringWithRange:NSMakeRange(0, 1)];
            NSString *green = [string substringWithRange:NSMakeRange(1, 1)];
            NSString *blue = [string substringWithRange:NSMakeRange(2, 1)];
            string = [NSString stringWithFormat:@"%1$@%1$@%2$@%2$@%3$@%3$@ff", red, green, blue];
            break;
        }
        case 6:  {
            string = [string stringByAppendingString:@"ff"];
            break;
        }
        case 8: {
            //do nothing
            break;
        }
        default: {
            
#ifdef DEBUG
            //unsupported format
            NSLog(@"Unsupported color string format: %@", string);
#endif
            return nil;
        }
    }
    uint32_t rgba;
    NSScanner *scanner = [NSScanner scannerWithString:string];
    [scanner scanHexInt:&rgba];
    return [self ci_colorWithRGBAValue:rgba];
}

+ (instancetype)ci_colorWithRGBAValue:(uint32_t)rgba {
    CGFloat red = ((rgba & 0xFF000000) >> 24) / 255.0f;
    CGFloat green = ((rgba & 0x00FF0000) >> 16) / 255.0f;
    CGFloat blue = ((rgba & 0x0000FF00) >> 8) / 255.0f;
    CGFloat alpha = (rgba & 0x000000FF) / 255.0f;
    return [UIColor colorWithRed:red green:green blue:blue alpha:alpha];
}

@end
