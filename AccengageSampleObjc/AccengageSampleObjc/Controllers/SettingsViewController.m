//
//  SettingsViewController.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "SettingsViewController.h"
#import "AppDelegate.h"

@implementation SettingsCell

- (void)awakeFromNib {
    [super awakeFromNib];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
    [self.status setOn:selected animated:animated];
}

@end

typedef NS_ENUM(NSUInteger, SettingsCellType) {
    SettingsCellTypeSample,
    SettingsCellTypeSwitch
};

@interface SettingsViewController ()
@property(nonatomic, strong) NSArray *settings;
@end

@implementation SettingsViewController

static NSString * const reuseIdentifierSample = @"SimpleCell";
static NSString * const reuseIdentifierSwitch = @"SwitchCell";
static NSString * const reuseIdentifierFooter = @"FooterCell";

static NSString * const cellTypeKey = @"cellTypeKey";
static NSString * const cellTitleKey = @"cellTitleKey";
static NSString * const cellDetailsKey = @"cellDetailsKey";

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSDictionary *userName = @{cellTypeKey: @(SettingsCellTypeSample),
                               cellTitleKey: @"Edit the user display name"};
    
    
    NSDictionary *inappLock = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                cellTitleKey: @"Lock InApp messages display",
                                cellDetailsKey: @"On: if you want to disable inApp Notifications \nOff: to enable inApp Notifications"};
    
    NSDictionary *beacons = @{cellTypeKey: @(SettingsCellTypeSwitch),
                              cellTitleKey: @"Enable beacons service",
                              cellDetailsKey: @"On: if you want to enable beacons service \nOff: to disable it"};
    
    NSDictionary *geofences = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                cellTitleKey: @"Enable geofencing service",
                                cellDetailsKey: @"On: if you want to enable geofencing service \nOff: to disable it"};
    
    self.settings = @[userName, inappLock, beacons, geofences ];
    
    self.accengageAlias = @"SETTINGS";
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self updateSelectionsAnimated:NO];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.settings.count;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = nil;
    
    NSDictionary *item =  self.settings[indexPath.section];
    
    SettingsCellType type = [item[cellTypeKey] integerValue];
    
    if (type == SettingsCellTypeSwitch) {
        cell = [tableView dequeueReusableCellWithIdentifier:reuseIdentifierSwitch];
        
        ((SettingsCell*)cell).title.text = item[cellTitleKey];
    }
    else {
        cell = [tableView dequeueReusableCellWithIdentifier:reuseIdentifierSample];
        cell.textLabel.text = item[cellTitleKey];
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    switch (indexPath.section) {
        case 0:{
            [self setUserName];
            [tableView deselectRowAtIndexPath:indexPath animated:YES];
            break;
        }
        default:
            [self setStatus:YES forIndex:indexPath.section];
            break;
    }
}

- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSDictionary *item =  self.settings[indexPath.section];
    SettingsCellType type = [item[cellTypeKey] integerValue];
    
    if (type == SettingsCellTypeSwitch) {
        [self setStatus:NO forIndex:indexPath.section];
        
    }
}

- (UIView *)tableView:(UITableView *)tableView
viewForFooterInSection:(NSInteger)section {
    UITableViewCell *view = [tableView dequeueReusableCellWithIdentifier:reuseIdentifierFooter];
    
    NSDictionary *item =  self.settings[section];
    NSString *details = item[cellDetailsKey];
    
    if (!details) {
        return nil;
    }
    
    view.textLabel.text = details;
    view.textLabel.lineBreakMode = NSLineBreakByWordWrapping;
    view.textLabel.numberOfLines = 0;
    return view;
}

- (CGFloat)tableView:(UITableView *)tableView
heightForFooterInSection:(NSInteger)section {
    
    return [self heightForText:self.settings[section][cellDetailsKey]];
}

#pragma mark - Actions


- (void)setUserName {
    SCLAlertView *alert = [self editionAlertView];
    
    SCLTextView *textField = [alert addTextField:@"User name"];
    
    [alert addButton:@"Send" actionBlock:^(void) {
        
        NSString* text = textField.text ?: @"";
        [[NSUserDefaults standardUserDefaults] setValue:text forKey:@"user.name"];
        [Accengage updateDeviceInfo:@{@"user_name": text}];
    }];
    
    NSString *name =[[NSUserDefaults standardUserDefaults] valueForKey:@"user.name"];
    NSString *subtitle = name ? [NSString stringWithFormat:@"The current name is: %@", name] : @"";
    [alert showEdit:nil title:@"User's name" subTitle:subtitle closeButtonTitle:@"Cancel" duration:0.0f];
}


- (void)setStatus:(BOOL)status forIndex:(NSInteger)index {
    switch (index) {
            // InApp lock
        case 1:
            [BMA4SInAppNotification setNotificationLock:status];
            break;
        case 2:
            [SampleHelpers setBeaconServiceEnabled:status];
            break;
        case 3:
            [SampleHelpers setGeofenceServiceEnabled:status];
            break;
            
        default:
            break;
    }
}
    
#pragma mark - Helpers

- (SCLAlertView*)editionAlertView {
    SCLAlertView *alert = [[SCLAlertView alloc] initWithNewWindow];
    
    alert.shouldDismissOnTapOutside = YES;
    alert.customViewColor = SAMPLE_BLUE_COLOR;
    alert.hideAnimationType = FadeOut;
    alert.showAnimationType = FadeIn;
    
    return alert;
}

- (BOOL)statusForIndex:(NSInteger)index {
    
    switch (index) {
        case 1:
            return  [BMA4SInAppNotification notificationLock];
        case 2:
            return  [SampleHelpers isBeaconServiceEnabled];
        case 3:
            return  [SampleHelpers isGeofenceServiceEnabled];
            
        default:
            return NO;
    }
}

- (void)updateSelectionsAnimated:(BOOL)animated {
    for (int i = 2; i < self.settings.count; i++) {
        NSIndexPath *indexPath = [NSIndexPath indexPathForRow:0 inSection:i];
        if ([self statusForIndex:i]) {
            [self.tableView selectRowAtIndexPath:indexPath
                                        animated:animated
                                  scrollPosition:UITableViewScrollPositionNone];
        } else {
            [self.tableView deselectRowAtIndexPath:indexPath animated:animated];
        }
    }
}

- (float)heightForText:(NSString *)text {
    CGSize maximumLabelSize =
    CGSizeMake(self.tableView.bounds.size.width, FLT_MAX);
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
    CGSize expectedLabelSize = [text sizeWithFont:[UIFont systemFontOfSize:14.]
                                constrainedToSize:maximumLabelSize
                                    lineBreakMode:NSLineBreakByWordWrapping];
#pragma clang diagnostic pop
    
    return expectedLabelSize.height + 10;
}

@end
