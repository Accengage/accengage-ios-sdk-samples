//
//  InboxDetailsViewController.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "InboxDetailsViewController.h"
#import "InboxTools.h"

@interface InboxDetailsViewController () <UIWebViewDelegate>
@property(strong, nonatomic) IBOutlet UILabel *sender;
@property(strong, nonatomic) IBOutlet UILabel *receiptDate;
@property(strong, nonatomic) IBOutlet UILabel *detailsView;
@property(strong, nonatomic) IBOutlet UIToolbar *toolbar;
@property(strong, nonatomic) IBOutlet UIWebView *webview;
@property(strong, nonatomic) IBOutlet UIActivityIndicatorView *loader;
@property(strong, nonatomic) IBOutlet UILabel *subjectLabel;
@property(strong, nonatomic) IBOutlet UILabel *category;
@property(strong, nonatomic) IBOutlet UITextView *textView;
@property(strong, nonatomic) IBOutlet UIImageView *iconMsg;
@property(strong, nonatomic) IBOutlet UIButton *transitionButton;
@property(strong, nonatomic) IBOutletCollection(UIView) NSArray *detailCollection;

@property(strong, nonatomic) IBOutlet UIView *detailView;
@property(strong, nonatomic) IBOutlet UIView *richContentView;


@end

@implementation InboxDetailsViewController

//------------------------------------------------------------------------------
#pragma mark - View life cycle

//------------------------------------------------------------------------------
- (void)viewDidLoad {
  [super viewDidLoad];

  // Setup tool bar with custom buttons
  [self setupToolbar];

  //
  self.subjectLabel.text = self.message.title;
  self.sender.text =
      [NSString stringWithFormat:NSLocalizedString(@"Expéditeur : %@", nil),
                                 self.message.from];

  // Category
    NSString *categorie = self.message.category;
  self.category.text = categorie ?: @"";
  self.category.backgroundColor =
      [InboxTools colorForCategory:categorie];

  self.receiptDate.text = [NSString
      stringWithFormat:NSLocalizedString(@"Reçu : %@", nil),
                       [InboxTools labelTextForDate:self.message.date]];

  self.detailsView.text = self.message.text;

  switch (self.content.type) {
    case BMA4SMessageContentTypeText: {
      [self.webview setHidden:YES];
      (self.textView).text = self.content.body;
      break;
    }
    case BMA4SMessageContentTypeWeb:{
      [self.textView setHidden:YES];
      [self.loader startAnimating];
      self.webview.alpha = 0;
      self.webview.delegate = self;
      [self.webview
       loadRequest:[NSURLRequest requestWithURL:
                    [NSURL URLWithString:self.content.body]]];
      break;
    }
  }

    NSString *iconUrl = self.message.iconUrl;

  if (iconUrl.length > 0) {
    NSMutableURLRequest *request = [NSMutableURLRequest
        requestWithURL:[NSURL URLWithString:iconUrl]];
    [NSURLConnection
        sendAsynchronousRequest:request
                          queue:[NSOperationQueue mainQueue]
              completionHandler:^(NSURLResponse *response, NSData *data,
                                  NSError *error) {
                if (!error)
                  self.iconMsg.image =
                      [[UIImage alloc] initWithData:data];
              }];
  } else
    [self.iconMsg setHidden:YES];
  
  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(deviceOrientationDidChangeNotification:)
                                               name:UIApplicationDidChangeStatusBarOrientationNotification
                                             object:nil];
  
  [self updateForDeviceOrientation];
}

#pragma mark - UI management

//------------------------------------------------------------------------------
- (void)setupToolbar {
  UIBarButtonItem *space = [[UIBarButtonItem alloc]
      initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace
                           target:nil
                           action:nil];

  UIBarButtonItem *markAsRead =
  [self barButtomWithTitle:self.message.isRead?NSLocalizedString(@"Mark as unread", nil):NSLocalizedString(@"Mark as read", nil)
                         style:UIBarButtonItemStylePlain
                        action:@selector(markAsUnread)];

  UIBarButtonItem *archive =
      [self barButtomWithTitle:self.message.isArchived?NSLocalizedString(@"Restore", nil):NSLocalizedString(@"Delete", nil)
                         style:UIBarButtonItemStylePlain
                        action:@selector(archive)];
  
  NSMutableArray *buttons =
      [@[ space, markAsRead, space, archive, space] mutableCopy];
  
  NSInteger i = 0;
  for (BMA4SInBoxButton *button in self.content.buttons) {
    UIBarButtonItem *aButton =
        [self barButtomWithTitle:button.title
                           style:UIBarButtonItemStylePlain
                          action:@selector(interact:)];

    aButton.tag = i;
    [buttons addObjectsFromArray:@[ aButton, space]];
    i++;
  }

  [self.toolbar setItems:buttons animated:NO];
}


- (void) updateDetailsViewFrame {
  
  if (!self.transitionButton.selected) {
    self.headerHeight.constant = 155;
  }
  else {
    self.headerHeight.constant = self.transitionButton.frame.size.height;
  }
  
}

- (void)updateToolbarFrame {
  CGRect toolbarFrame = self.toolbar.frame;
  
  self.toolBarBottom.constant = -1;
  
  if (self.transitionButton.selected) {
    self.toolBarBottom.constant -= toolbarFrame.size.height;
  }
}

- (void) updateDetailsAlpha {
  for (UIView *view in self.detailCollection) {
    view.alpha = !self.transitionButton.selected;
  }
}

- (void) updateSubjectFrame {
  CGRect subjecFrame = self.subjectLabel.frame;
  
  if (!self.transitionButton.selected) {
    subjecFrame.origin.x = self.sender.frame.origin.x;
    subjecFrame.origin.y = self.iconMsg.frame.origin.y;
    subjecFrame.size.height = self.sender.frame.size.height;
  }
  else {
    subjecFrame.origin.x = self.iconMsg.frame.origin.x;
    subjecFrame.origin.y = self.transitionButton.frame.origin.y;
    subjecFrame.size.height = self.transitionButton.frame.size.height;
  }
  
  self.subjectLabel.frame = subjecFrame;
}

- (void)updateForDeviceOrientation{
  UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
  
  if(UIInterfaceOrientationIsLandscape(orientation)) {
    [self showDetails:NO];
  }
  else if(UIInterfaceOrientationIsPortrait(orientation)) {
    [self showDetails:YES];
  }
}

#pragma mark - Tools

//------------------------------------------------------------------------------
- (UIBarButtonItem *)barButtomWithTitle:(NSString *)title
                                  style:(UIBarButtonItemStyle)style
                                 action:(SEL)action {

  return [[UIBarButtonItem alloc] initWithTitle:title
                                           style:style
                                          target:self
                                          action:action];
}

#pragma mark - Webview delegate
- (void)webViewDidFinishLoad:(UIWebView *)webView {
  [self stopLoadingAnimation];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
  [self stopLoadingAnimation];
}

- (void)stopLoadingAnimation {
  if (self.loader.isAnimating) {
    self.webview.alpha = 1;
  }
  [self.loader stopAnimating];
}
#pragma mark - Actions

//------------------------------------------------------------------------------
- (void)markAsUnread {
  if (self.message.isRead) {
    [self.message markAsUnread];
  }
  else {
    [self.message markAsRead];
  }
  [self setupToolbar];
}

//------------------------------------------------------------------------------
- (void)archive {
  if (self.message.isArchived) {
    [self.message unarchive];
  }
  else {
    [self.message archive];
  }
  [self setupToolbar];
}

//------------------------------------------------------------------------------
- (void)interact:(id)sender {
  NSInteger tag = [sender tag];
  [self.content.buttons[tag] interact];
}

- (IBAction)showDetailView:(id)sender {
  [self showDetails:self.transitionButton.selected];
}

- (void)showDetails:(BOOL)show {
  
  if (show != self.transitionButton.selected) {
    return;
  }
  
  self.transitionButton.selected = !show;
  
  [self updateDetailsViewFrame];
    [self updateToolbarFrame];

  [UIView animateWithDuration:0.2 animations:^{
    [self.view layoutIfNeeded]; // Called on parent view
    [self updateDetailsAlpha];
    [self updateSubjectFrame];
  } completion:^(BOOL finished) {
  }];
}


#pragma mark - Orientation change notification

- (void)deviceOrientationDidChangeNotification:(NSNotification*)note
{
  UIInterfaceOrientation newOrientation = [UIApplication sharedApplication].statusBarOrientation;
  UIInterfaceOrientation oldOrientation = (UIInterfaceOrientation)[note.userInfo[UIApplicationStatusBarOrientationUserInfoKey] integerValue];
  
  if (UIInterfaceOrientationIsPortrait(newOrientation) != UIInterfaceOrientationIsPortrait(oldOrientation)) {
    [self updateForDeviceOrientation];
  }
}

@end
