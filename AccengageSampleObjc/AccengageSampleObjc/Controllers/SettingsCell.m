//
//  SettingsCell.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//


#import "SettingsCell.h"

@interface SettingsCell()
@property (strong, nonatomic) ACCDeviceTag *deviceTag;
@end


@implementation SettingsCell

- (void)awakeFromNib {
    [super awakeFromNib];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
    [self.status setOn:selected animated:animated];
}

@end
