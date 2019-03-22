//
//  ViewController.m
//  GoogleTagManagerBridge
//
//  Created by Bastien MATTHAI on 18/03/2019.
//  Copyright © 2019 ACC. All rights reserved.
//

#import "ViewController.h"
#import "Firebase/Firebase.h"
#import <Accengage/Accengage.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (IBAction)trackEventAction:(id)sender {
    
    [FIRAnalytics logEventWithName:@"track_event" parameters:@{@"acc_event_id":@2000, @"prenom":@"Mouna", @"valeur":@20, @"date":[self stringFromDate:[NSDate date]], @"bool":@false}];
    
}

- (IBAction)trackLeadAction:(id)sender {
    [FIRAnalytics logEventWithName:@"track_lead" parameters:@{@"acc_lead_label":@"Instagram", @"acc_lead_value":@"OK"}];

}

- (IBAction)trackAddToCartAction:(id)sender {
    
    [FIRAnalytics logEventWithName:@"track_add_to_cart" parameters:@{@"acc_cart_id":@"12DQSD213", @"acc_item_id":@"6fbf6b83", @"acc_item_label":@"iphone", @"acc_item_category":@"iPhone 7+", @"acc_item_currency":@"EUR", @"acc_item_price":@909, @"acc_item_quantity":@1}];
    
}

- (IBAction)trackPurshaceAction:(id)sender {
    
    ACCCartItem *item = [ACCCartItem itemWithId:@"12DQSD213" name:@"iphone" brand:nil category:@"iPhone 7+" price:909 quantity:1];
    [FIRAnalytics logEventWithName:@"track_purchase" parameters:@{@"acc_purchase_id":@"12DQSD213", @"acc_purchase_currency":@"EUR", @"acc_purchase_total_price":@1704, @"KEY_PURCHASE_ITEMS":@[item]}];
}

- (IBAction)trackSetUdiAction:(id)sender {
    
    [FIRAnalytics logEventWithName:@"set_udi" parameters:@{@"acc_udi_key":@"name", @"acc_udi_value":@"Mouna"}];
    [FIRAnalytics logEventWithName:@"set_udi" parameters:@{@"acc_udi_key":@"entier", @"acc_udi_value":@1234}];
    [FIRAnalytics logEventWithName:@"set_udi" parameters:@{@"acc_udi_key":@"date", @"acc_udi_value":[self stringFromDate:[NSDate date]]}];
    
}

- (IBAction)trackIncrementUdiAction:(id)sender {
    
    //increment new_udi_int field
    [FIRAnalytics logEventWithName:@"increment_udi" parameters:@{@"acc_udi_increment_value":@3}];
    
}

- (IBAction)trackDecrementUDIAction:(id)sender {
    
    //decrement new_udi_int field
    [FIRAnalytics logEventWithName:@"decrement_udi" parameters:@{@"acc_udi_decrement_value":@1}];
    
}

- (IBAction)trackDeleteUdiAction:(id)sender {
    
     [FIRAnalytics logEventWithName:@"delete_udi" parameters:@{@"acc_udi_delete_key":@"name"}];
    
}

- (NSString *)stringFromDate:(NSDate *)date {
    
    // Convert to new Date Format
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss zzz"];
    NSString *newDate = [dateFormatter stringFromDate:date];
    return newDate;
    
}

@end
