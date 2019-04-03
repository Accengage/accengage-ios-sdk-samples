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
#import "ACCCustomTagProvider.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UILabel *sharedID;

@end

@implementation ViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    self.sharedID.text = [[Accengage shared] accengageId];
    
}

- (IBAction)trackEventAction:(id)sender {
    
    [FIRAnalytics logEventWithName:ACTION_TRACK_EVENT parameters:@{KEY_EVENT_ID:@2000, @"prenom":@"Accengage", @"valeur":@20, @"date":[ACCCustomTagProvider stringFromDate:[NSDate date]], @"bool":@false}];
    
}

- (IBAction)trackLeadAction:(id)sender {

    [FIRAnalytics logEventWithName:ACTION_TRACK_LEAD parameters:@{KEY_LEAD_LABEL:@"Instagram", KEY_LEAD_VALUE:@"OK"}];
    
}

- (IBAction)trackAddToCartAction:(id)sender {
    
    [FIRAnalytics logEventWithName:ACTION_TRACK_ADD_TO_CART parameters:@{KEY_CART_ID:@"12DQSD213", KEY_ITEM_ID:@"6fbf6b83", KEY_ITEM_NAME:@"iphone", KEY_ITEM_CATEGORY:@"iPhone 7+", KEY_ITEM_CURRENCY:@"EUR", KEY_ITEM_PRICE:@909, KEY_ITEM_QUANTITY:@1}];
    
}

- (IBAction)trackPurshaceAction:(id)sender {
    
    ACCCartItem *item = [ACCCartItem itemWithId:@"12DQSD213" name:@"12DQSD213" brand:nil category:@"iPhone 7+" price:909 quantity:1];
    
    NSString *jsonitems = [ACCCustomTagProvider jsonFromCartItems:@[item]] ? : @"";
    
    [FIRAnalytics logEventWithName:ACTION_TRACK_PURCHASE parameters:@{KEY_PURCHASE_ID:@"12DQSD213", KEY_PURCHASE_CURRENCY:@"EUR", KEY_PURCHASE_TOTAL_PRICE:@1704, KEY_PURCHASE_ITEMS:jsonitems}];
    
}

- (IBAction)trackSetUdiAction:(id)sender {
    
    [FIRAnalytics logEventWithName:ACTION_SET_UDI parameters:@{@"acc_udi_key":@"name", @"acc_udi_value":@"Accengage"}];
    [FIRAnalytics logEventWithName:ACTION_SET_UDI parameters:@{@"acc_udi_key":@"entier", @"acc_udi_value":@1234}];
    [FIRAnalytics logEventWithName:ACTION_SET_UDI parameters:@{@"acc_udi_key":@"date", @"acc_udi_value":[ACCCustomTagProvider stringFromDate:[NSDate date]]}];
    
}

- (IBAction)trackIncrementUdiAction:(id)sender {
    
    //increment new_udi_int field
    [FIRAnalytics logEventWithName:ACTION_INCREMENT_UDI parameters:@{@"acc_udi_increment_value":@3}];
    
}

- (IBAction)trackDecrementUDIAction:(id)sender {
    
    //decrement new_udi_int field
    [FIRAnalytics logEventWithName:ACTION_DECREMENT_UDI parameters:@{@"acc_udi_decrement_value":@1}];
    
}

- (IBAction)trackDeleteUdiAction:(id)sender {
    
     [FIRAnalytics logEventWithName:ACTION_DELETE_UDI parameters:@{@"acc_udi_delete_key":@"name"}];
    
}

@end
