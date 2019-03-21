//
//  ViewController.m
//  GoogleTagManagerBridge
//
//  Created by Bastien MATTHAI on 18/03/2019.
//  Copyright © 2019 ACC. All rights reserved.
//

#import "ViewController.h"
#import "Firebase/Firebase.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (IBAction)trackEventAction:(id)sender {
    [FIRAnalytics logEventWithName:@"track_event" parameters:@{@"prenom":@"Mouna", @"valeur":20, @"date":[NSDate date], @"bool":false}];
    
}

- (IBAction)trackLeadAction:(id)sender {
    [FIRAnalytics logEventWithName:@"track_lead" parameters:@{@"acc_lead_label":@"testlabel", @"acc_lead_value":@"test_value"}];

}

- (IBAction)trackAddToCartAction:(id)sender {
    [FIRAnalytics logEventWithName:@"track_add_to_cart" parameters:@{@"acc_lead_label":@"testlabel", @"acc_lead_value":@"test_value"}];
    
}

- (IBAction)trackPurshaceAction:(id)sender {
    Acc.trackCart('12DQSD213', '6fbf6b83', 1, 'iphone', 'iPhone 7+', 909, 'EUR');
    [FIRAnalytics logEventWithName:@"track_purchase" parameters:@{@"acc_lead_label":@"testlabel", @"acc_lead_value":@"test_value"}];
    
}

- (IBAction)trackSetUdiAction:(id)sender {
    [FIRAnalytics logEventWithName:@"set_udi" parameters:@{@"acc_lead_label":@"testlabel", @"acc_lead_value":@"test_value"}];
    
}

- (IBAction)trackIncrementUdiAction:(id)sender {
    [FIRAnalytics logEventWithName:@"increment_udi" parameters:@{@"acc_lead_label":@"testlabel", @"acc_lead_value":@"test_value"}];
    
}

- (IBAction)trackDecrementUDIAction:(id)sender {
    [FIRAnalytics logEventWithName:@"decrement_udi" parameters:@{@"acc_lead_label":@"testlabel", @"acc_lead_value":@"test_value"}];
    
}

- (IBAction)trackDeleteUdiAction:(id)sender {
    [FIRAnalytics logEventWithName:@"delete_udi" parameters:@{@"acc_lead_label":@"testlabel", @"acc_lead_value":@"test_value"}];
    
}

@end
