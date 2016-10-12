//
//  InBoxMessageTableViewCell.h
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface InBoxMessageTableViewCell : UITableViewCell

@property(nonatomic, assign) NSInteger index;

- (void)setMessage:(BMA4SInBoxMessage *)msg;
- (void)setLoading;

@end
