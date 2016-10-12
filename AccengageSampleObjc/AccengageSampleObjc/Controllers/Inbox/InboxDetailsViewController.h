//
//  InboxDetailsViewController.h
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "BaseViewController.h"

@interface InboxDetailsViewController : BaseViewController
@property (nonatomic, strong) BMA4SInBoxMessage* message;
@property (nonatomic, strong) BMA4SInBoxMessageContent* content;

@property (strong, nonatomic) IBOutlet NSLayoutConstraint *headerHeight;
@property (strong, nonatomic) IBOutlet NSLayoutConstraint *toolBarBottom;

@end
