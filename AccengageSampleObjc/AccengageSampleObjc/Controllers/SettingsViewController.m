//
//  SettingsViewController.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "SettingsViewController.h"
#import "AppDelegate.h"

/*
 * Push notification setting segue identifier
 */
static NSString * const pushNotificationSettingIdentifier = @"showPushNotificationSettings";

@interface SettingsViewController ()
@end

@implementation SettingsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSDictionary *userName = @{cellTypeKey: @(SettingsCellTypeSample),
                               cellTitleKey: @"Edit the user display name"};
    
    
    NSDictionary *inappLock = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                cellTitleKey: @"Lock InApp messages display",
                                cellDetailsKey: @"On : if you want to disable inApp Notifications \nOff : to enable inApp Notifications"};
    
    NSDictionary *beacons = @{cellTypeKey: @(SettingsCellTypeSwitch),
                              cellTitleKey: @"Enable beacons service",
                              cellDetailsKey: @"On : if you want to enable beacons service \nOff : to disable it"};
    
    NSDictionary *geofences = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                cellTitleKey: @"Enable geofencing service",
                                cellDetailsKey: @"On : if you want to enable geofencing service \nOff : to disable it"};
    
    NSDictionary *dataOptin = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                cellTitleKey: @"Enable user data collection",
                                cellDetailsKey: @"On : if you want to enable user data collection\nOff : to disable user data collection"};
    
    NSDictionary *pushNotificationSetting = @{cellTypeKey: @(SettingsCellTypeSample),
                                cellTitleKey: @"Push notifications settings"};
    
    NSDictionary *registerRemoteNotification = @{
                                                 cellTypeKey: @(SettingsCellTypeSample),
                                                 cellTitleKey: @"Register for remote notifications"};
    
    self.settings = @[userName, inappLock, beacons, geofences, dataOptin, pushNotificationSetting, registerRemoteNotification];
    
    self.accengageAlias = @"SETTINGS";
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self updateSelectionsAnimated:NO];
}

#pragma mark - Table view data source

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    
    UITableViewCell *cell = [super tableView:tableView cellForRowAtIndexPath:indexPath];
    if (cell) {
        if (indexPath.section == 6) {
            cell.accessoryType = UITableViewCellAccessoryNone;
        }
    }
    return cell;
}

/**
 * Called once the specified row is selected.
 */
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    switch (indexPath.section) {
        case 0:{
            [self setUserName];
            [tableView deselectRowAtIndexPath:indexPath animated:YES];
            break;
        }
        case 5:{
            [self performSegueWithIdentifier:pushNotificationSettingIdentifier sender:self];
            [tableView deselectRowAtIndexPath:indexPath animated:YES];
            break;
        }
        case 6:{
            [[Accengage push] registerForUserNotificationsWithOptions:ACCNotificationOptionAlert|ACCNotificationOptionBadge|ACCNotificationOptionSound];
            [tableView deselectRowAtIndexPath:indexPath animated:YES];
            break;
        }
        default:
            [self setStatus:YES forIndex:indexPath.section];
            break;
    }
}

/**
 * Called once the specified row is deselected.
 */
- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSDictionary *item =  self.settings[indexPath.section];
    SettingsCellType type = [item[cellTypeKey] integerValue];
    
    if (type == SettingsCellTypeSwitch) {
        [self setStatus:NO forIndex:indexPath.section];
        
    }
}

#pragma mark - Actions

- (void)setUserName {
    SCLAlertView *alert = [self editionAlertView];
    
    SCLTextView *textField = [alert addTextField:@"User name"];
    
    [alert addButton:@"Send" actionBlock:^(void) {
        
        NSString* text = textField.text ?: @"";
        [[NSUserDefaults standardUserDefaults] setValue:text forKey:@"user.name"];
        ACCDeviceInformationSet *deviceInfo = [[ACCDeviceInformationSet alloc] init];
        [deviceInfo setString:text forKey:@"user_name"];
        [[Accengage profile] updateDeviceInformation:deviceInfo withCompletionHandler:^(NSError * _Nullable error) {
            if (error) {
                NSLog(@"*** UDI error : %@", [error localizedDescription]);
            }
        }];
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
        case 4:
            
            // Updating data collection parameters according to UISwitch value given by parameter "status".
            
            [Accengage setDataOptInEnabled:status];
            [Accengage setGeolocOptInEnabled:status];
            [[NSUserDefaults standardUserDefaults] setBool:status forKey:@"optin"];
            if (status == YES) {
                [[Accengage push]registerForUserNotificationsWithOptions:ACCNotificationOptionAlert|ACCNotificationOptionBadge|ACCNotificationOptionSound];
            } else {
                [SampleHelpers setGeofenceServiceEnabled:NO];
                [SampleHelpers setBeaconServiceEnabled:NO];
                [self updateSelectionsAnimated:NO];
            }
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
        case 4:
            return  [Accengage isDataOptInEnabled];
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


@end
