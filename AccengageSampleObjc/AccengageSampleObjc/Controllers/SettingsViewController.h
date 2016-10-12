//
//  SettingsViewController.h
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "BaseTableViewController.h"

@interface SettingsCell : UITableViewCell

@property (strong, nonatomic) IBOutlet UILabel *title;
@property (strong, nonatomic) IBOutlet UISwitch *status;

@end


@interface SettingsViewController : BaseTableViewController

@end
