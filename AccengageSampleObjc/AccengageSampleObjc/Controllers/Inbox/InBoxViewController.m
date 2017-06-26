//
//  InBoxViewController.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "InBoxViewController.h"
#import "InBoxMessageTableViewCell.h"
#import "InboxDetailsViewController.h"


@interface InBoxViewController ()
@property(strong, retain) IBOutlet UITableView *tableView;
@property(strong, nonatomic) IBOutlet UIToolbar *toolbar;
@property(strong, nonatomic) IBOutlet UIBarButtonItem *markMessage;
@property(strong, nonatomic) IBOutlet UIBarButtonItem *archiveMessage;
@property(nonatomic, strong) BMA4SInBox *inbox;
@property(nonatomic, strong) UIRefreshControl *refreshControl;
@end

@implementation InBoxViewController


#pragma mark - View life cycle
//------------------------------------------------------------------------------
- (void)viewDidLoad {
  [super viewDidLoad];

  self.accengageAlias = @"INBOX";
    
  // Register for inbox notication
  NSNotificationCenter *notificationCenter =
      [NSNotificationCenter defaultCenter];
  [notificationCenter addObserver:self
                         selector:@selector(inboxChanged:)
                             name:BMA4SInBoxDataChanged
                           object:nil];

  // Register for cell notification
  [notificationCenter addObserver:self
                         selector:@selector(inboxRefresh:)
                             name:@"RefreshInBox"
                           object:nil];

  // Set Title
  // Ex : Inbox (3)
  self.title =
      [NSString stringWithFormat:@"Inbox (%lu)",
                                 (unsigned long)self.inbox.unreadMessageCount];

// Initialize the refresh control.
  if ([UIRefreshControl class]) {
    self.refreshControl = [[UIRefreshControl alloc] init];
    self.refreshControl.backgroundColor = [UIColor colorWithWhite:0 alpha:0.1];
    [self.refreshControl addTarget:self
                            action:@selector(reloadData)
                  forControlEvents:UIControlEventValueChanged];
    [self.tableView addSubview:self.refreshControl];
    
    dispatch_async(dispatch_get_main_queue(), ^{
      [self.refreshControl beginRefreshing];
      [self.refreshControl endRefreshing];
    });
  }

  // Add Edit Button
    UIBarButtonItem *rightButton = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"edit"]
                                                                    style:UIBarButtonItemStylePlain
                                                                   target:self
                                                                   action:@selector(startEditing:)];
    rightButton.tintColor = [UIColor whiteColor];

  if (self.navigationItem) {
    self.navigationItem.rightBarButtonItem = rightButton;
  }

  // Reload Inbox Data
  [self reloadData];
}

//------------------------------------------------------------------------------
- (void)viewWillAppear:(BOOL)animated {
  [super viewWillAppear:animated];

  // Desable edition
  [self activeEditionState:NO];
  [self.view addSubview:self.toolbar];
}

#pragma mark - Actions
//------------------------------------------------------------------------------
- (IBAction)startEditing:(id)sender {
  [self activeEditionState:!self.tableView.editing];
}

//------------------------------------------------------------------------------
- (IBAction)markAsRead:(id)sender {
  for (NSIndexPath *indexPath in (self.tableView).indexPathsForSelectedRows) {
    [self.inbox obtainMessageAtIndex:indexPath.row
        loaded:^(BMA4SInBoxMessage *message, NSUInteger requestedIndex) {
          if (message.isRead)
            [message markAsUnread];
          else
            [message markAsRead];
        }
        onError:^(NSUInteger requestedIndex){
            // Should not append
        }];
  }
}

//------------------------------------------------------------------------------
- (IBAction)archiveMessage:(id)sender {
  for (NSIndexPath *indexPath in (self.tableView).indexPathsForSelectedRows) {
    [self.inbox obtainMessageAtIndex:indexPath.row
        loaded:^(BMA4SInBoxMessage *message, NSUInteger requestedIndex) {
          if ([message isArchived])
            [message unarchive];
          else
            [message archive];
        }
        onError:^(NSUInteger requestedIndex){
            // Should not append
        }];
  }
}

//------------------------------------------------------------------------------
- (void)reloadData {
  [BMA4SInBox obtainMessagesWithCompletionHandler:^(BMA4SInBoxLoadingResult result, BMA4SInBox *inbox) {
    self.inbox = inbox;
    [self updateUIandData];
  }];
}

#pragma mark - UI management

//------------------------------------------------------------------------------
- (void)updateUIandData {
  // update table content
  [self.tableView reloadData];

  // title updating
  self.title =
      [NSString stringWithFormat:@"Inbox (%lu)",
                                 (unsigned long)self.inbox.unreadMessageCount];

  (self.navigationController.tabBarItem).badgeValue = [NSString
                        stringWithFormat:@"%lu", (unsigned long)self.inbox
                                                     .unreadMessageCount];

  // End the refreshing
  if (self.refreshControl) {
    // Get Last update date
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"MMM d, h:mm a";
    NSString *title =
        [NSString stringWithFormat:NSLocalizedString(@"Last update: %@", nil),
                                   [formatter stringFromDate:[NSDate date]]];
    NSDictionary *attrsDictionary =
        @{NSForegroundColorAttributeName : [UIColor darkGrayColor]};
    NSAttributedString *attributedTitle = [[NSAttributedString alloc]
        initWithString:title
            attributes:attrsDictionary];
    self.refreshControl.attributedTitle = attributedTitle;
    [self.refreshControl endRefreshing];
  }
}

//------------------------------------------------------------------------------
- (void)updateToolBarPosition {
    CGRect toolbarFrame = self.toolbar.frame;
    
    self.toolBarBottom.constant = -1;
    
    if (!self.tableView.editing) {
        self.toolBarBottom.constant -= toolbarFrame.size.height;
    }

  [UIView animateWithDuration:0.3f
                   animations:^{
                       [self.view layoutIfNeeded];
                   }];
}

//------------------------------------------------------------------------------
- (void)activeEditionState:(BOOL)actived {
  [self.tableView setEditing:actived animated:YES];

    UIImage *image = [UIImage imageNamed:@"edit"];
    
  if (self.tableView.editing) {
      image = [UIImage imageNamed:@"save"];

  }
    
    self.navigationItem.rightBarButtonItem.image = image;

  [self updateToolBarPosition];
  [self updateUIandData];
}

#pragma mark - Notications

//------------------------------------------------------------------------------
- (void)inboxChanged:(NSNotification *)notif {
  [self updateUIandData];
}

//------------------------------------------------------------------------------
- (void)inboxRefresh:(NSNotification *)notif {
  [self.tableView reloadData];
}

#pragma mark - Table view data source

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
  NSInteger index = indexPath.row;
  [self.inbox obtainMessageAtIndex:index loaded:^(BMA4SInBoxMessage *message, NSUInteger requestedIndex) {
    if (index == requestedIndex && !message.isDisplayed) {
      [message trackDisplay];
    }
  } onError:nil];
}

//------------------------------------------------------------------------------
- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
  InBoxMessageTableViewCell *cell = (InBoxMessageTableViewCell *)
      [tableView dequeueReusableCellWithIdentifier:@"messageCell"
                                      forIndexPath:indexPath];

  cell.index = indexPath.row;
  [cell setLoading];
  [self.inbox obtainMessageAtIndex:indexPath.row
      loaded:^(BMA4SInBoxMessage *message, NSUInteger requestedIndex) {
        if (cell.index == requestedIndex)
          [cell setMessage:message];
      }
      onError:^(NSUInteger requestedIndex) {
        if (cell.index == requestedIndex) {
          // Error
        }
      }];

  cell.accessoryType = UITableViewCellAccessoryNone;
  return cell;
}

//------------------------------------------------------------------------------
- (NSInteger)tableView:(UITableView *)tableView
    numberOfRowsInSection:(NSInteger)section {
  return self.inbox ? [self.inbox size] : 0;
}

#pragma mark Table view delegate

//------------------------------------------------------------------------------
- (void)tableView:(UITableView *)tableView
    didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
  
    if (!self.tableView.editing) {
        [tableView deselectRowAtIndexPath:indexPath animated:NO];
        [self.inbox obtainMessageAtIndex:indexPath.row
                                  loaded:^(BMA4SInBoxMessage *message, NSUInteger requestedIndex) {
                                      [message trackOpening];
                                      [message interactWithDisplayHandler:^(BMA4SInBoxMessage *message, BMA4SInBoxMessageContent *content) {
                                           InboxDetailsViewController *controller = (InboxDetailsViewController *)[self.storyboard instantiateViewControllerWithIdentifier: @"InboxDetailsViewController"];
                                           if (controller) {
                                               controller.message = message;
                                               controller.content = content;
                                               [self.navigationController pushViewController:controller
                                                                                    animated:YES];
                                           }
                                       }];
                                  }
                                 onError:nil];
    }
}

@end
