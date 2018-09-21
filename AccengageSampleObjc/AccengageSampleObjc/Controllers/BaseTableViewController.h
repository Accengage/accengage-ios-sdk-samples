//
//  BaseTableViewController.h
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BaseTableViewController : UITableViewController

@property(nonatomic, strong) NSArray *settings;

- (IBAction)pop:(id)sender;
- (IBAction)dismiss:(id)sender;
@end
