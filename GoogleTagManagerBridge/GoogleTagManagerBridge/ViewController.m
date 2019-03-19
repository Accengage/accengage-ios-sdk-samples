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

- (IBAction)trackLeadAction:(id)sender {
    [FIRAnalytics logEventWithName:@"track_lead" parameters:    @{@"acc_lead_label":@"testlabel", @"acc_lead_value":@"test_value"}];

}

@end
