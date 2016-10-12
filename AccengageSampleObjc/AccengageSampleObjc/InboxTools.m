//
//  InboxTools.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "InboxTools.h"

@implementation InboxTools


+ (UIColor*) colorForCategory:(NSString*)category {
    if (category && category.length > 0) {
        if ([category.lowercaseString isEqualToString:@"promos"]) {
            return BLUE_COLOR ;
        }
        else if ([category.lowercaseString isEqualToString:@"nouveauté"]) {
            return [UIColor orangeColor];
        }
    }
    return [UIColor clearColor];
}

+ (NSString*) labelTextForDate:(NSDate*)date {
  NSDate* today = [NSDate date];
  
  NSCalendar *gregorianCalendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
  
  NSInteger year = [gregorianCalendar components:NSCalendarUnitYear
                                         fromDate:date
                                           toDate:today
                                          options:0].year;
  
  NSInteger month = [gregorianCalendar components:NSCalendarUnitMonth
                                          fromDate:date
                                            toDate:today
                                           options:0].month;
  
  NSInteger day = [gregorianCalendar components:NSCalendarUnitDay
                                        fromDate:date
                                          toDate:today
                                         options:0].day;
  
  BOOL Yesterday  = ([gregorianCalendar components:NSCalendarUnitDay
                                        fromDate:today].day - [gregorianCalendar components:NSCalendarUnitDay
                                                                              fromDate:date].day) == 1;

  if (year >= 1)
    return [NSString stringWithFormat:NSLocalizedString(@"%ld years ago", nil), (long)year];
  else if ((month >= 1) && (month <= 12))
    return [NSString stringWithFormat:NSLocalizedString(@"%ld months ago", nil), (long)month];
  else if ((day > 1) && (day <= 31))
    return [NSString stringWithFormat:NSLocalizedString(@"%ld days ago", nil), (long)day];
  else if (Yesterday)
    return NSLocalizedString(@"Yesterday", nil);
  else {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    dateFormatter.timeZone = [NSTimeZone localTimeZone];
    
    dateFormatter.dateFormat = @"HH:mm";
    NSString *dateString = [dateFormatter stringFromDate:date];
    return [NSString stringWithFormat:NSLocalizedString(@"Today %@", nil), dateString];
  }
  
  return @"";
}

@end
