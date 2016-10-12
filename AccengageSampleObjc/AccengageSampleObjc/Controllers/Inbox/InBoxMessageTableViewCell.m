//
//  InBoxMessageTableViewCell.m
//  AccengageSampleObjc
//
//  Copyright © 2016 Accengage. All rights reserved.
//

#import "InBoxMessageTableViewCell.h"
#import "InboxTools.h"

@interface InBoxMessageTableViewCell ()
@property(strong, nonatomic) IBOutlet UIView *statusMessage;
@property(strong, nonatomic) IBOutlet UIImageView *iconMsg;
@property(strong, nonatomic) IBOutlet UILabel *subject;
@property(strong, nonatomic) IBOutlet UILabel *category;
@property(strong, nonatomic) IBOutlet UILabel *content;
@property(strong, nonatomic) IBOutlet UILabel *date;
@property(nonatomic, strong) BMA4SInBoxMessage *messageInfo;
@end

@implementation InBoxMessageTableViewCell


#pragma mark - Operations

- (void)setMessage:(BMA4SInBoxMessage *)msg {
  self.messageInfo = msg;

  (self.subject).text = msg.title;
  (self.content).text = msg.text;
  self.date.text = [InboxTools labelTextForDate:msg.date];

    NSString *categorie = msg.category;
  self.category.text = categorie ?: @"";
  self.category.backgroundColor =
      [InboxTools colorForCategory:categorie];

  if (msg.isRead) {
    (self.subject).textColor = [UIColor colorWithWhite:0.4f alpha:1.0f];
    (self.content).textColor = [UIColor colorWithWhite:0.4f alpha:1.0f];
    (self.statusMessage).backgroundColor = [UIColor whiteColor];
  } else {
    (self.subject).textColor = [UIColor blackColor];
    (self.content).textColor = [UIColor blackColor];
    [self.statusMessage setBackgroundColor:BLUE_COLOR];
  }

  if ([msg isArchived])
    (self.statusMessage).backgroundColor = [UIColor redColor];

    NSString *iconUrl = msg.iconUrl;

  if (iconUrl.length > 0) {
    [self.iconMsg setHidden:NO];
    NSMutableURLRequest *request =
        [NSMutableURLRequest requestWithURL:[NSURL URLWithString:iconUrl]];
    [NSURLConnection
        sendAsynchronousRequest:request
                          queue:[NSOperationQueue mainQueue]
              completionHandler:^(NSURLResponse *response, NSData *data,
                                  NSError *error) {
                if (!error) {
                  self.iconMsg.image =
                      [[UIImage alloc] initWithData:data];
                }
              }];
  } else
    [self.iconMsg setHidden:YES];
}

- (void)setLoading {
  (self.subject).text = @"";
  (self.content).text = @"";
}

@end
