//
//  ACCCustomTagProvider.m
//  GoogleTagManagerBridge
//
//  Created by Bastien MATTHAI on 18/03/2019.
//  Copyright © 2019 ACC. All rights reserved.
//

#import "ACCCustomTagProvider.h"
//#import "Accengage/Accengage.h"

@implementation ACCCustomTagProvider

- (NSObject*)executeWithParameters:(NSDictionary*)parameters {
    if (parameters[@"acc_action"] == nil) {
        return nil;
    }
    
    if ([parameters[@"acc_action"] isEqualToString:@"decrement_udi"]) {

    }
    else if([parameters[@"acc_action"] isEqualToString:@"delete_udi"]) {
    
    }
    else if([parameters[@"acc_action"] isEqualToString:@"increment_udi"]) {
        
    }
    else if([parameters[@"acc_action"] isEqualToString:@"set_udi"]) {
        
    }
    else if([parameters[@"acc_action"] isEqualToString:@"track_add_to_cart"]) {
        
    }
    else if([parameters[@"acc_action"] isEqualToString:@"track_lead"]) {
        
    }
    else if([parameters[@"acc_action"] isEqualToString:@"track_purchase"]) {
        
    }
    return nil;
}


- (void) trackLead:(NSDictionary*)parameters {
//    Accengage trac
//    [Accengage trackLead:@"" value:@""];
//acc_lead_label
//acc_lead_value
}


@end
