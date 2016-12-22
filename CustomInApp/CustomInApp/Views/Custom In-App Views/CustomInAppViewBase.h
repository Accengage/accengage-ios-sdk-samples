//
//  CustomInAppViewBase.h
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Accengage/Accengage.h>

#import "CIBlockButton.h"
#import "UIImageView+WebCache.h"
#import "UIColor+Helper.h"
#import "NSObject+Helper.h"

static NSString * const CIContainerPrefix = @"container";

static NSString * const CITitleLabelPrefix = @"title";
static NSString * const CISubtitleLabelPrefix = @"subtitle";
static NSString * const CIBodyLabelPrefix = @"body";

static NSString * const CILeftButtonPrefix = @"left.btn";
static NSString * const CIRightButtonPrefix = @"right.btn";
static NSString * const CIBottomButtonPrefix = @"bottom.btn";
static NSString * const CICloseButtonPrefix = @"close.btn";

static NSString * const CIHeaderImagePrefixKey = @"header.img";
static NSString * const CIIconImagePrefiKey = @"icon.img";

static NSString * const CITextKey = @"text";
static NSString * const CIColorKey = @"color";
static NSString * const CIBackgroundColorKey = @"bg.color";
static NSString * const CIBorderColorKey = @"border.color";
static NSString * const CIBorderWidthKey = @"border.width";
static NSString * const CIBorderRadiusKey = @"border.radius";

static NSString * const CIHiddenKey = @"hidden";
static NSString * const CIPathKey = @"url";

static NSString * const CIActionTypeKey = @"action.type";
static NSString * const CIActionValueKey = @"action.value";
static NSString * const CIActionExtraKey = @"action.extra";

static NSString * const CIActionTypeUDI = @"udi";
static NSString * const CIActionTypeURL = @"url";
static NSString * const CIActionTypeEvent = @"event";
static NSString * const CIActionTypeRequest = @"request";

NSString * KeyFactory(NSString *prefix, NSString *suffix);

@interface CIViewPresenter: NSObject

+ (void)presentButton:(CIBlockButton *)button withParams:(NSDictionary *)params prefix:(NSString *)prefix action:(ActionBlock)action;

+ (void)presentImage:(UIImageView *)image withParams:(NSDictionary *)params prefix:(NSString *)prefix;

+ (void)presentView:(UIView *)view withParams:(NSDictionary *)params prefix:(NSString *)prefix;

+ (void)presentView:(UIView *)view withParams:(NSDictionary *)params prefix:(NSString *)prefix textOptional:(BOOL)textOptional;

+ (void)setCornerRadius:(NSNumber *)radius corners:(UIRectCorner)corners view:(UIView *)view;

@end

@interface CustomInAppViewBase : UIView

@property (strong, nonatomic) BMA4SInAppMessage *message;

- (void)setupWithMessage:(BMA4SInAppMessage *)message;

@end
