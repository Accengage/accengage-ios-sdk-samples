//
//  CustomizableTextInterstitial.m
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "CustomizableTextInterstitial.h"

@implementation CustomizableTextInterstitial

- (void)setupWithMessage:(BMA4SInAppMessage *)message {
    
    [super setupWithMessage:message];
    
    NSMutableDictionary *params = message.displayCustomParams.mutableCopy;
    params[[NSString stringWithFormat:@"%@.%@",CIBodyLabelPrefix,CITextKey]] = ((BMA4SInAppTextMessage *)message).body ?: @"";
    params[[NSString stringWithFormat:@"%@.%@",CICloseButtonPrefix,CITextKey]] = @"X";

    // Container
    [CIViewPresenter presentView:self.container withParams:params prefix:CIContainerPrefix textOptional:YES];

    // Title label
    [CIViewPresenter presentView:self.titleLabel withParams:params prefix:CITitleLabelPrefix];
    self.titleLabel.text =  [self.titleLabel.text uppercaseString];
    
    // Subtitle Label
    [CIViewPresenter presentView:self.subtitleLabel withParams:params prefix:CISubtitleLabelPrefix];

    // Body Label
    [CIViewPresenter presentView:self.bodyLabel withParams:params prefix:CIBodyLabelPrefix];

    // Header image
    [CIViewPresenter presentImage:self.headerImageView withParams:params prefix:CIHeaderImagePrefixKey];
    
    if (self.headerImageView.superview) {
        [CIViewPresenter setCornerRadius:@(self.container.layer.cornerRadius) corners:(UIRectCornerTopLeft | UIRectCornerTopRight) view:self.headerImageView];
    }
    
    // Top icon image
    [CIViewPresenter presentImage:self.iconImageView withParams:params prefix:CIIconImagePrefiKey];

    // Top icon bg
    if (self.iconImageView.superview) {
        [CIViewPresenter presentView:self.iconContainer withParams:params prefix:CIIconImagePrefiKey textOptional:YES];
    }
    else {
        [self.iconContainer removeFromSuperview];
    }

    __weak __typeof(self) wself = self;
    // Actions buttons
    [CIViewPresenter presentButton:self.leftButton withParams:params prefix:CILeftButtonPrefix action:^{
        wself.message.clickCompletionHandler(@"");
    }];
    
    [CIViewPresenter presentButton:self.rightButton withParams:params prefix:CIRightButtonPrefix action:^{
        wself.message.clickCompletionHandler(@"");
    }];

    [CIViewPresenter presentButton:self.footerButton withParams:params prefix:CIBottomButtonPrefix action:^{
        wself.message.clickCompletionHandler(@"");
    }];

    [CIViewPresenter presentButton:self.closeButton withParams:params prefix:CICloseButtonPrefix action:^{
        wself.message.dismissCompletionHandler();
    }];
}

@end
