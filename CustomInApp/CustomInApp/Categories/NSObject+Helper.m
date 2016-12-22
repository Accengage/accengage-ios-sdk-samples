//
//  NSObject+Helper.m
//  CustomInApp
//
//  Created by Yassir Barchi on 22/11/2016.
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "NSObject+Helper.h"

@implementation NSObject (Helper)

- (BOOL)ci_isEmpty {
    
    if ([self isEqual:[NSNull null]]) {
        return YES;
    }
    
    // NSArray or NSDictionary
    if ([self respondsToSelector:@selector(count)] && [(NSArray *)self count] == 0) {
        return YES;
    }
    
    // NSData or NSString
    if ([self respondsToSelector:@selector(length)] && [(NSData *)self length] == 0) {
        return YES;
    }
    
    // Avoid strings with only white spaces
    if ([self isKindOfClass:[NSString class]]) {
        NSString *trimed = [(NSString *)self stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        return (trimed.length == 0);
    }
    
    return NO;
}

@end
