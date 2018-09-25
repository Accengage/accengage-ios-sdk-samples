//
//  SettingsCell.h
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//


static NSString * const reuseIdentifierSample = @"SimpleCell";
static NSString * const reuseIdentifierSwitch = @"SwitchCell";
static NSString * const reuseIdentifierFooter = @"FooterCell";

static NSString * const cellTypeKey = @"cellTypeKey";
static NSString * const cellTitleKey = @"cellTitleKey";
static NSString * const cellDetailsKey = @"cellDetailsKey";

typedef NS_ENUM(NSUInteger, SettingsCellType) {
    SettingsCellTypeSample,
    SettingsCellTypeSwitch
};

@interface SettingsCell : UITableViewCell

@property (strong, nonatomic) IBOutlet UILabel *title;
@property (strong, nonatomic) IBOutlet UISwitch *status;

@end
