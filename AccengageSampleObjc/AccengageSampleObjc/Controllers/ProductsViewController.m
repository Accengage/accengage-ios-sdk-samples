//
//  ProductsViewController.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "ProductsViewController.h"
#import "SettingsCell.h"

static NSString * const reuseIdentifier = @"Cell";

@interface ProductsViewController ()

@end

@implementation ProductsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSMutableArray *array = [[NSMutableArray alloc] init];
    for (int i = 0; i < 100; i++)
    {
        NSDictionary *userName = @{cellTypeKey: @(SettingsCellTypeSample),
                                   cellTitleKey: @"Product", cellDetailsKey:[NSString stringWithFormat:@"%d", i]};
        [array addObject:userName];
    }

    self.settings = array;
    
    self.accengageAlias = @"PRODUCTS";
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 100;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseIdentifier];
    
    cell.textLabel.text = @"Product";
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%d", (int)(indexPath.row)];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    SCLAlertView *alert = [[SCLAlertView alloc] initWithNewWindow];
    
    SCLTextView *textField = [alert addTextField:@"Enter the quantity"];
    textField.keyboardType = UIKeyboardTypeNumberPad;
    
    SCLTextView *textField2 = [alert addTextField:@"Enter the price"];
    textField2.keyboardType = UIKeyboardTypeNumberPad;

    alert.shouldDismissOnTapOutside = YES;
    alert.customViewColor = SAMPLE_BLUE_COLOR;
    alert.hideAnimationType = FadeOut;
    alert.showAnimationType = FadeIn;
    
    __block NSInteger index = indexPath.row;
    [alert addButton:@"Send" actionBlock:^(void) {
        NSLog(@"Text value: %@", textField.text);
        
        NSString *product =  [NSString stringWithFormat:@"Product %ld", (long)index];
        
        NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
        f.numberStyle = NSNumberFormatterDecimalStyle;
        NSInteger quantity = [f numberFromString:textField.text].integerValue;

        NSInteger price = [f numberFromString:textField2.text].integerValue;
        
        ACCCartItem *item = [ACCCartItem itemWithId:product name:product brand:@"Brand" category:@"Product" price:price quantity:quantity];
        [Accengage trackPurchase:@"dePurchase" currency:@"EUR" items:@[item] amount:@(quantity * price)];
    }];
    
    [alert showEdit:nil title:@"How much ?" subTitle:@"" closeButtonTitle:@"Cancel" duration:0.0f];
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

@end
