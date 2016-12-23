//
//  CustomizableTextInterstitial.h
//  CustomInApp
//
//  Created by Yassir Barchi on 21/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "CustomInAppViewBase.h"

@interface CustomizableTextInterstitial : CustomInAppViewBase

@property (weak, nonatomic) IBOutlet UIView *container;

@property (weak, nonatomic) IBOutlet UIImageView *headerImageView;
@property (weak, nonatomic) IBOutlet UIImageView *iconImageView;

@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UILabel *subtitleLabel;
@property (weak, nonatomic) IBOutlet UILabel *bodyLabel;
@property (weak, nonatomic) IBOutlet UIView *iconContainer;

@property (weak, nonatomic) IBOutlet CIBlockButton *leftButton;
@property (weak, nonatomic) IBOutlet CIBlockButton *rightButton;
@property (weak, nonatomic) IBOutlet CIBlockButton *footerButton;

@property (weak, nonatomic) IBOutlet CIBlockButton *closeButton;

@end
