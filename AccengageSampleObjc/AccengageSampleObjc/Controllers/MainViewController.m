//
//  MainViewController.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "MainViewController.h"

@interface MainViewController () 
@property (nonatomic, strong) NSArray *items;
@end

@implementation MainViewController

static NSString * const reuseIdentifier = @"Cell";

static NSString * const itemImageNameKey = @"itemImageNameKey";
static NSString * const itemLabelTextKey = @"itemLabelTextKey";

- (void)viewDidLoad {
    [super viewDidLoad];
    
     self.clearsSelectionOnViewWillAppear = YES;
    
    UIImage* logoImage = [UIImage imageNamed:@"header"];
    self.navigationItem.titleView = [[UIImageView alloc] initWithImage:logoImage];
    
    self.items = @[@{itemImageNameKey:@"mostViewed.jpg", itemLabelTextKey:@"Most viewed"},
                   @{itemImageNameKey:@"media.jpg", itemLabelTextKey:@"Multimedia"},
                   @{itemImageNameKey:@"technology.jpg", itemLabelTextKey:@"Technology"},
                   @{itemImageNameKey:@"art.jpg", itemLabelTextKey:@"Art & Design"},
                   @{itemImageNameKey:@"business.jpg", itemLabelTextKey:@"Business"}];

    self.accengageAlias = @"DEMO";
}

#pragma mark - Actions

- (IBAction)likeUs {
    [Accengage trackLead:@"Facebook" value:@"like"];
    
    SCLAlertView *alert = [[SCLAlertView alloc] initWithNewWindow];
    [alert showSuccess:@"Thank you!" subTitle:@"Thanks for liking us on Facebook!" closeButtonTitle:@"Close" duration:3.0f];
}

#pragma mark - <UICollectionViewDataSource>

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}


- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.items.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:reuseIdentifier forIndexPath:indexPath];
    
    UIImageView *imageView = [cell viewWithTag:1];
    imageView.image = [UIImage imageNamed:self.items[indexPath.row][itemImageNameKey]];
    
    UILabel *label = [cell viewWithTag:2];
    label.text = self.items[indexPath.row][itemLabelTextKey];
    
    // Configure the cell
    cell.layer.masksToBounds = NO;
    cell.layer.shadowOffset = CGSizeMake(0, 1);
    cell.layer.shadowRadius = 1.;
    cell.layer.shadowColor = [UIColor blackColor].CGColor;
    cell.layer.shadowOpacity = 0.2;
    
    return cell;
}

#pragma mark - <UICollectionViewDelegate>

- (CGSize)collectionView:(UICollectionView *)collectionView
                  layout:(UICollectionViewLayout *)collectionViewLayout
  sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    double width = (collectionView.bounds.size.width - 30) / 2;    
    return CGSizeMake(width, width*1.2);
}

@end
