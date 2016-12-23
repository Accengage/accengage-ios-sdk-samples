//
//  CustomInAppViewBase.m
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "CustomInAppViewBase.h"
#import <Accengage/Accengage.h>

@implementation CIViewPresenter

+ (void)presentButton:(CIBlockButton *)button withParams:(NSDictionary *)params prefix:(NSString *)prefix action:(ActionBlock)action {
    
    [self presentView:button withParams:params prefix:prefix];
    
    if (button.superview) {
        ActionBlock finalAction = [self actionWithParams:params prefix:prefix default:action];
        [button handleTouchUpInsideEventWithBlock:finalAction];
    }
}

+ (void)presentImage:(UIImageView *)image withParams:(NSDictionary *)params prefix:(NSString *)prefix {
    NSString *path = params[KeyFactory(prefix, CIPathKey)];
    
    if (path && ![path ci_isEmpty]) {
        
        if (ImageURLIsLocal(path)) {
            [image setImage:[UIImage imageNamed:path]];
        }
        else {
            [image sd_setImageWithURL:[NSURL URLWithString:path]];
        }
    }
    else {
        [image removeFromSuperview];
    }
}

+ (void)presentView:(UIView *)view withParams:(NSDictionary *)params prefix:(NSString *)prefix {
    [self presentView:view withParams:params prefix:prefix textOptional:NO];
}

+ (void)presentView:(UIView *)view withParams:(NSDictionary *)params prefix:(NSString *)prefix textOptional:(BOOL)textOptional {
    
    NSString *text = params[KeyFactory(prefix, CITextKey)];
    NSString *hidden = params[KeyFactory(prefix, CIHiddenKey)];

    if (((text && ![text ci_isEmpty]) || textOptional) && !hidden) {
        
        NSString *textCSSColor = params[KeyFactory(prefix, CIColorKey)];
        UIColor *textColor = [UIColor ci_colorWithCSS:textCSSColor];
        
        // Text & Color: UIButton
        if ([view isKindOfClass:UIButton.class]) {
            [(UIButton *)view setTitle:text forState:UIControlStateNormal];
            
            // Text Color
            if (textColor) {
                [(UIButton *)view setTitleColor:textColor forState:UIControlStateNormal];
            }
        }
        // Text & Color: UILabel, UITextField or UITextView
        else if ([view respondsToSelector:@selector(setText:)]) {
            [(UILabel *)view setText:text];
            
            // Text Color
            if (textColor) {
                [(UILabel *)view setTextColor:textColor];
            }
        }
        
        // Background Color
        NSString *backgroundCSSColor = params[KeyFactory(prefix, CIBackgroundColorKey)];
        UIColor *backgroundColor = [UIColor ci_colorWithCSS:backgroundCSSColor];
        
        if (backgroundColor) {
            view.backgroundColor = backgroundColor;
        }
        
        // Borders
        NSString *borderWidth = params[KeyFactory(prefix, CIBorderWidthKey)];
        
        if (borderWidth && ![borderWidth ci_isEmpty]) {
            view.layer.borderWidth = borderWidth.floatValue;
            
            // Border Color
            NSString *borderCSSColor = params[KeyFactory(prefix, CIBorderColorKey)];
            UIColor *borderColor = [UIColor ci_colorWithCSS:borderCSSColor];
            
            if (borderColor) {
                view.layer.borderColor = borderColor.CGColor;
            }
        }
        
        // Radius
        NSString *cornerRadius = params[KeyFactory(prefix, CIBorderRadiusKey)];
        if (cornerRadius && ![cornerRadius ci_isEmpty]) {
            view.layer.cornerRadius = cornerRadius.floatValue;
        }

    }
    else {
        [view removeFromSuperview];
    }
}

///--------------------------------------
#pragma mark - Action parser
///--------------------------------------

+ (ActionBlock)actionWithParams:(NSDictionary *)params prefix:(NSString *)prefix default:(ActionBlock)defaultAction {
    
    NSString *actionType = params[KeyFactory(prefix, CIActionTypeKey)];
    NSString *actionValue = params[KeyFactory(prefix, CIActionValueKey)];
    NSString *actionExtra = params[KeyFactory(prefix, CIActionExtraKey)];
    
    if (![actionType ci_isEmpty] && ![actionValue ci_isEmpty]) {
        
        // Update device information
        if ([actionType isEqualToString:CIActionTypeUDI]) {
            if (actionExtra) {
                return ^() {
                    [Accengage updateDeviceInfo:@{actionValue: actionExtra}];
                    if (defaultAction) {
                        defaultAction();
                    }
                };
            }
        }
        
        // URL
        else if ([actionType isEqualToString:CIActionTypeURL]) {
            return ^() {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:actionValue]];
                if (defaultAction) {
                    defaultAction();
                }
            };
        }
        
        // Event
        else if ([actionType isEqualToString:CIActionTypeEvent]) {
            return ^() {
                [Accengage trackEvent:actionValue.integerValue withParameters:@[actionExtra?:@""]];
                if (defaultAction) {
                    defaultAction();
                }
            };
        }
        
        // Request
        else if ([actionType isEqualToString:CIActionTypeRequest]) {
            return ^() {
                NSURL *URL = [NSURL URLWithString:actionValue];
                NSURLRequest *request = [NSURLRequest requestWithURL:URL];
                
                NSURLSession *session = [NSURLSession sharedSession];
                NSURLSessionDataTask *task = [session dataTaskWithRequest:request
                                                        completionHandler: ^(NSData *data, NSURLResponse *response, NSError *error) {
                                                            NSLog(@"%@",data ? [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] : error.localizedDescription);
                                                        }];
                [task resume];
                
                if (defaultAction) {
                    defaultAction();
                }
            };
        }
        
    }
    
    return defaultAction;
}

///--------------------------------------
#pragma mark - Helpers
///--------------------------------------

NSString * KeyFactory(NSString *prefix, NSString *suffix) {
    
    if (prefix && ![prefix ci_isEmpty]) {
        return [NSString stringWithFormat:@"%@.%@",prefix, suffix];
    }
    
    return suffix;
}

BOOL ImageURLIsLocal(NSString *imageURL) {
    if ([[imageURL lowercaseString] hasPrefix:@"http"]) {
        return NO;
    }
    
    return YES;
}

+ (void)setCornerRadius:(NSNumber *)radius corners:(UIRectCorner)corners view:(UIView *)view {
    
    if (!view) {
        return;
    }
    
    UIBezierPath *maskPath = [UIBezierPath bezierPathWithRoundedRect:view.bounds byRoundingCorners:corners cornerRadii:CGSizeMake(radius.floatValue, radius.floatValue)];
    
    CAShapeLayer *maskLayer = [[CAShapeLayer alloc] init];
    maskLayer.frame = view.bounds;
    maskLayer.path  = maskPath.CGPath;
    view.layer.mask = maskLayer;
}

@end

@implementation CustomInAppViewBase

- (void)setupWithMessage:(BMA4SInAppMessage *)message {
    self.message = message;
    
    [CIViewPresenter presentView:self withParams:message.displayCustomParams prefix:nil textOptional:YES];
}

@end
