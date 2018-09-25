//
//  PushNotificationSettingsViewController
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "PushNotificationSettingsViewController.h"

static NSString * const MY_CATEGORY = @"item";

@interface PushNotificationSettingsViewController () <UITableViewDelegate, UITableViewDataSource>

@end

@implementation PushNotificationSettingsViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    //Activate data optin if it's disabled
    [Accengage setDataOptInEnabled:YES];
    
    NSDictionary *multimedia = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                cellTitleKey: @"Multimedia",
                                cellDetailsKey: @"On : if you want to receive multimedia notifications\nOff : to not receive multimedia notifications"};
    
    NSDictionary *technology = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                 cellTitleKey: @"Technology",
                                 cellDetailsKey: @"On : if you want to receive technology notifications\nOff : to not receive technology notifications"};
    
    NSDictionary *artEtDesign = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                 cellTitleKey: @"Art et design",
                                 cellDetailsKey: @"On : if you want to receive art and design notifications\nOff : to not receive art and design notifications"};
    
    NSDictionary *business = @{cellTypeKey: @(SettingsCellTypeSwitch),
                                 cellTitleKey: @"Business",
                                 cellDetailsKey: @"On : if you want to receive business notifications\nOff : to not receive business notifications"};
    
    super.settings = @[multimedia, technology, artEtDesign, business];
    
    self.accengageAlias = @"PUSH_SETTINGS";
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self updateSelectionsAnimated:NO];
}

#pragma mark - Table view data source

/**
 * Called once the specified row is selected.
 */
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self setStatus:YES forIndex:indexPath.section];
}

/**
 * Called once the specified row is deselected.
 */
- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self setStatus:NO forIndex:indexPath.section];
}

#pragma mark - Helpers

/**
 * Set/delete device tag
 *
 @param status the
 @param index the selected table view item status
 */
- (void)setStatus:(BOOL)status forIndex:(NSInteger)index {
    
    NSDictionary *item =  self.settings[index];
    NSString *identifier = item[cellTitleKey];
    
    ACCDeviceTag *deviceTag = [[ACCDeviceTag alloc] initWithCategory:MY_CATEGORY identifier:identifier];
    if (deviceTag) {
        //Set the device tag parameters
        [deviceTag setString:@"name" forKey:@"name"];
        [deviceTag setNumber:[NSNumber numberWithInt:5] forKey:@"number"];
        [deviceTag setDate:[NSDate date] forKey:@"date"];
        
        NSString *key = [NSString stringWithFormat:@"%@-%@", MY_CATEGORY, identifier];
        if (status == YES) {
            //Set the device tag
            [[Accengage profile] setDeviceTag:deviceTag];
            [[NSUserDefaults standardUserDefaults] setObject:identifier forKey:key];
        } else {
            //Delete the device tag
            [[Accengage profile] deleteDeviceTag:deviceTag];
            [[NSUserDefaults standardUserDefaults] removeObjectForKey:key];
        }
    }
}

- (void)updateSelectionsAnimated:(BOOL)animated {
    for (int i = 0; i < self.settings.count; i++) {
        NSIndexPath *indexPath = [NSIndexPath indexPathForRow:0 inSection:i];
        
        NSDictionary *item =  self.settings[indexPath.section];
        NSString* key = [NSString stringWithFormat:@"%@-%@", MY_CATEGORY, item[cellTitleKey]];
        NSString* value = [[NSUserDefaults standardUserDefaults] objectForKey:key];
        if (value) {
            [self.tableView selectRowAtIndexPath:indexPath
                                        animated:animated
                                  scrollPosition:UITableViewScrollPositionNone];
        } else {
            [self.tableView deselectRowAtIndexPath:indexPath animated:animated];
        }
    }
}

@end
