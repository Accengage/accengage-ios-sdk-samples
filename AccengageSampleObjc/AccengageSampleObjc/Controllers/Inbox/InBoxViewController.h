//
//  InBoxViewController.h
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "BaseViewController.h"

@interface InBoxViewController : BaseViewController <UITableViewDataSource, UITableViewDelegate>

@property (strong, nonatomic) IBOutlet NSLayoutConstraint *toolBarBottom;

@end
