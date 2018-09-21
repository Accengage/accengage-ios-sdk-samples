//
//  BaseTableViewController.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "BaseTableViewController.h"
#import "SettingsCell.h"

@interface BaseTableViewController ()

@end

@implementation BaseTableViewController
@synthesize settings;

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIImage* logoImage = [UIImage imageNamed:@"header"];
    self.navigationItem.titleView = [[UIImageView alloc] initWithImage:logoImage];
    
    self.clearsSelectionOnViewWillAppear = YES;
    self.navigationController.interactivePopGestureRecognizer.delegate = (id<UIGestureRecognizerDelegate>)self;
    [[UINavigationBar appearance] setTintColor:[UIColor whiteColor]];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return settings.count;
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

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section {
    
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

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {
    
    return [self heightForText:self.settings[section][cellDetailsKey]];
}

- (IBAction)pop:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}
- (IBAction)dismiss:(id)sender {
    [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer {
    return YES;
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
