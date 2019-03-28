/*!
 * @file ACCCustomTagProvider.h
 * @author Accengage
 * @copyright  © 2010 - present Accengage, Inc. All rights reserved.
 */


#import "ACCCustomTagProvider.h"
#import "Accengage/Accengage.h"

/* Accengage Actions */
NSString *const KEY_ACTION = @"acc_action";
NSString *const ACTION_TRACK_EVENT = @"track_event";
NSString *const ACTION_TRACK_LEAD = @"track_lead";
NSString *const ACTION_TRACK_ADD_TO_CART = @"track_add_to_cart";
NSString *const ACTION_TRACK_PURCHASE = @"track_purchase";
NSString *const ACTION_SET_UDI = @"set_udi";
NSString *const ACTION_DELETE_UDI = @"delete_udi";
NSString *const ACTION_INCREMENT_UDI = @"increment_udi";
NSString *const ACTION_DECREMENT_UDI = @"decrement_udi";

/* Track Event */
NSString *const KEY_EVENT_ID = @"acc_event_id";

/* Track Lead */
NSString *const KEY_LEAD_LABEL = @"acc_lead_label";
NSString *const KEY_LEAD_VALUE = @"acc_lead_value";

/* Track Add To Cart */
NSString *const KEY_CART_ID = @"acc_cart_id";
NSString *const KEY_ITEM_ID = @"acc_item_id";
NSString *const KEY_ITEM_NAME = @"acc_item_label";
NSString *const KEY_ITEM_CATEGORY = @"acc_item_category";
NSString *const KEY_ITEM_CURRENCY = @"acc_item_currency";
NSString *const KEY_ITEM_PRICE = @"acc_item_price";
NSString *const KEY_ITEM_QUANTITY = @"acc_item_quantity";
NSString *const KEY_ITEM_BRAND = @"acc_item_brand";

/* Track Purchase */
NSString *const KEY_PURCHASE_ID = @"acc_purchase_id";
NSString *const KEY_PURCHASE_CURRENCY = @"acc_purchase_currency";
NSString *const KEY_PURCHASE_TOTAL_PRICE = @"acc_purchase_total_price";
NSString *const KEY_PURCHASE_ITEMS = @"acc_purchase_items";

/* Accengage date format */
NSString *const DATE_FORMAT = @"yyyy-MM-dd HH:mm:ss zzz";

@implementation ACCCustomTagProvider

///--------------------------------------
#pragma mark - TAGCustomFunction delegate -
///--------------------------------------

- (NSObject*)executeWithParameters:(NSDictionary*)parameters {
    
    if (!parameters) {
        NSLog(@"ACCCustomTagProvider | No parameters found");
        return nil;
    }
    
    NSString *acccengageAction = parameters[KEY_ACTION];
    if (!acccengageAction) {
        NSLog(@"ACCCustomTagProvider | No Accengage action found in parameters");
        return nil;
    }
    
    NSMutableDictionary *mutableDictionnary = [[NSMutableDictionary alloc] initWithDictionary:parameters];
    [mutableDictionnary removeObjectForKey:KEY_ACTION];
    NSDictionary *accengageParamters = mutableDictionnary;
    
    if ([acccengageAction isEqualToString:ACTION_TRACK_EVENT]) {
        
        [self parseTrackEventMessage:accengageParamters];
        
    } else if([acccengageAction isEqualToString:ACTION_TRACK_LEAD]) {
        
        [self parseTrackLeadMessage:accengageParamters];
        
    } else if ([acccengageAction isEqualToString:ACTION_TRACK_ADD_TO_CART]) {
        
        [self parseTrackCartMessage:accengageParamters];
        
    } else if([acccengageAction isEqualToString:ACTION_TRACK_PURCHASE]) {
        
        [self parseTrackPurchaseMessage:accengageParamters];
        
    } else if([acccengageAction isEqualToString:ACTION_SET_UDI]) {
        
        [self parseTrackSetUdi:accengageParamters];
        
    } else if([acccengageAction isEqualToString:ACTION_INCREMENT_UDI]) {
        
        [self parseTrackIncrementUdi:accengageParamters];
        
    } else if([acccengageAction isEqualToString:ACTION_DECREMENT_UDI]) {
        
        [self parseTrackDecrementUdi:accengageParamters];
        
    } else if([acccengageAction isEqualToString:ACTION_DELETE_UDI]) {
        
        [self parseTrackDeleteUdi:accengageParamters];
        
    }
    
    return nil;
    
}

///--------------------------------------
#pragma mark - Tracking -
///--------------------------------------

#pragma mark Track Event

- (void)parseTrackEventMessage:(NSDictionary *)parameters {
    
    NSNumber *type = parameters[KEY_EVENT_ID];
    if (!type) {
        NSLog(@"ACCCustomTagProvider | No %@ found in parameters. Can't send %@ action", KEY_EVENT_ID, ACTION_TRACK_EVENT);
        return;
    }
    
    ACCCustomEventParams *customEventParams = [[ACCCustomEventParams alloc] init];
    [parameters enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        
        if (!obj) {
            NSLog(@"ACCCustomTagProvider | The value of %@ is nil", key);
            return;
        }
        if ([key isEqualToString:KEY_EVENT_ID]) {
            return;
        }
        
        if ([obj isKindOfClass:[NSString class]]) {
            NSDate *date = [ACCCustomTagProvider dateFromString:obj];
            if (date) {
                [customEventParams setDate:date forKey:key];
            } else {
                [customEventParams setString:obj forKey:key];
            }
        } else if ([obj isKindOfClass:[NSNumber class]]) {
            [customEventParams setNumber:obj forKey:key];
        }
        
    }];
    
    [Accengage trackEvent:[type integerValue] withCustomParameters:customEventParams];
    
}

#pragma mark Track Lead

- (void)parseTrackLeadMessage:(NSDictionary *)parameters {
    
    NSString *label = parameters[KEY_LEAD_LABEL];
    NSString *value = parameters[KEY_LEAD_VALUE];
    
    if (!label || !value) {
        NSLog(@"ACCCustomTagProvider | The Label and the Value are required %@ ", parameters);
        return;
    }
    
    [Accengage trackLead:label value:value];
    
}

#pragma mark Track Cart

- (void)parseTrackCartMessage:(NSDictionary *)parameters {
    
    NSString *cartId = parameters[KEY_CART_ID];
    NSString *currency = parameters[KEY_ITEM_CURRENCY];
    NSString *itemId = parameters[KEY_ITEM_ID];
    NSString *itemName = parameters[KEY_ITEM_NAME];
    NSString *itemCategory = parameters[KEY_ITEM_CATEGORY];
    NSNumber *itemPrice = parameters[KEY_ITEM_PRICE];
    NSNumber *itemQuantity = parameters[KEY_ITEM_QUANTITY];
    NSString *brand = parameters[KEY_ITEM_BRAND];
    
    if (!cartId || !currency || !itemId || !itemName || !itemCategory  || !itemPrice || !itemQuantity) {
        NSLog(@"ACCCustomTagProvider | The acc_cart_id, acc_item_currency, acc_item_id, acc_item_label, acc_item_category, acc_item_price, and acc_item_quantity are required %@ ", parameters);
        return;
    }
    
    ACCCartItem *item = [ACCCartItem itemWithId:itemId name:itemName brand:brand category:itemCategory price:itemPrice.doubleValue quantity:itemQuantity.integerValue];
    
    [Accengage trackCart:cartId currency:currency item:item];
    
}

#pragma mark Track Purchase

- (void)parseTrackPurchaseMessage:(NSDictionary *)parameters {
    
    NSString *purchaseId = parameters[KEY_PURCHASE_ID];
    NSString *currency = parameters[KEY_PURCHASE_CURRENCY];
    NSNumber *price = parameters[KEY_PURCHASE_TOTAL_PRICE];
    NSString *items = parameters[KEY_PURCHASE_ITEMS];
    
    if (!purchaseId || !currency || !price) {
        NSLog(@"ACCCustomTagProvider | The acc_purchase_id, acc_purchase_currency and acc_purchase_total_price are required %@ ", parameters);
        return;
    }
    
    NSArray *cartItems = nil;
    if (items) {
        cartItems = [ACCCustomTagProvider cartItemsFromJson:items];
    }
    
    [Accengage trackPurchase:purchaseId currency:currency items:cartItems amount:price];
    
}

#pragma mark User Profile : UDI

- (void)parseTrackSetUdi:(NSDictionary *)parameters {
    
    ACCDeviceInformationSet * deviceInformationSet = [[ACCDeviceInformationSet alloc] init];
    
    [parameters enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        
        if (!obj) {
            NSLog(@"ACCCustomTagProvider | The value of %@ is nil", key);
            return;
        }
        
        if ([obj isKindOfClass:[NSString class]]) {
            NSDate *date = [ACCCustomTagProvider dateFromString:obj];
            if (date) {
                [deviceInformationSet setDate:date forKey:key];
            } else {
                [deviceInformationSet setString:obj forKey:key];
            }
        } else if ([obj isKindOfClass:[NSNumber class]]) {
            [deviceInformationSet setNumber:obj forKey:key];
        }
        
    }];
    
    [[Accengage profile] updateDeviceInformation:deviceInformationSet withCompletionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"ACCCustomTagProvider | Set UDI error %@", error.localizedDescription);
        }
    }];
    
}

- (void)parseTrackDeleteUdi:(NSDictionary *)parameters {
    
    ACCDeviceInformationSet * deviceInformationSet = [[ACCDeviceInformationSet alloc] init];
    [parameters enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        
        if (!obj) {
            NSLog(@"ACCCustomTagProvider | The value of %@ is nil", key);
            return;
        }
        
        [deviceInformationSet deleteValueForKey:key];
    }];
    
    [[Accengage profile] updateDeviceInformation:deviceInformationSet withCompletionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"ACCCustomTagProvider | Delete UDI error %@", error.localizedDescription);
        }
    }];
    
}

- (void)parseTrackIncrementUdi:(NSDictionary *)parameters {
    
    ACCDeviceInformationSet * deviceInformationSet = [[ACCDeviceInformationSet alloc] init];
    [parameters enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        
        if (!obj) {
            NSLog(@"ACCCustomTagProvider | The value of %@ is nil", key);
            return;
        }
        
        if (![obj isKindOfClass:[NSNumber class]]) {
            NSLog(@"ACCCustomTagProvider | The value of %@ should be of type NSNumber", key);
        }
        [deviceInformationSet incrementValueBy:obj forKey:key];
        
    }];
    
    [[Accengage profile] updateDeviceInformation:deviceInformationSet withCompletionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"ACCCustomTagProvider | Increment UDI error %@", error.localizedDescription);
        }
    }];
    
}

- (void)parseTrackDecrementUdi:(NSDictionary *)parameters {
    
    ACCDeviceInformationSet * deviceInformationSet = [[ACCDeviceInformationSet alloc] init];
    [parameters enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        
        if (!obj) {
            NSLog(@"ACCCustomTagProvider | The value of %@ is nil", key);
            return;
        }
        
        if (![obj isKindOfClass:[NSNumber class]]) {
            NSLog(@"ACCCustomTagProvider | The value of %@ should be of type NSNumber", key);
        }
        [deviceInformationSet decrementValueBy:obj forKey:key];
        
    }];
    
    [[Accengage profile] updateDeviceInformation:deviceInformationSet withCompletionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"ACCCustomTagProvider | Decrement UDI error %@", error.localizedDescription);
        }
    }];
    
}

///--------------------------------------
#pragma mark - Utils Methods -
///--------------------------------------

+ (NSString *)stringFromDate:(NSDate *)date {
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:DATE_FORMAT];
    return [dateFormatter stringFromDate:date];
    
}

+ (NSDate *)dateFromString:(NSString *)stringDate {
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:DATE_FORMAT];
    return [dateFormatter dateFromString:stringDate];
    
}

+ (NSString *)jsonFromCartItems:(NSArray *)cartItems {
    
    NSMutableArray *items = [[NSMutableArray alloc] init];
    
    [cartItems enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        
        if (![obj isKindOfClass:[ACCCartItem class]]) {
            NSLog(@"ACCCustomTagProvider | The object is not an ACCCartItem objet");
            return;
        }
        
        ACCCartItem *cartItem = obj;
        NSMutableDictionary *item = [[NSMutableDictionary alloc] init];
        if (cartItem.identifier) {
            [item setObject:cartItem.identifier forKey:KEY_ITEM_ID];
        }
        
        if (cartItem.name) {
            [item setObject:cartItem.name forKey:KEY_ITEM_NAME];
        }
        
        if (cartItem.brand) {
            [item setObject:cartItem.brand forKey:KEY_ITEM_BRAND];
        }
        
        if (cartItem.category) {
            [item setObject:cartItem.category forKey:KEY_ITEM_CATEGORY];
        }
        
        if (cartItem.price) {
            [item setObject:[NSNumber numberWithDouble:cartItem.price] forKey:KEY_ITEM_PRICE];
        }
        
        if (cartItem.quantity) {
            [item setObject:[NSNumber numberWithInteger:cartItem.quantity] forKey:KEY_ITEM_QUANTITY];
        }
        
        [items addObject:item];
        
    }];
    
    
    NSError *error = nil;
    NSData *json;
    NSString *jsonString = nil;
    
    if ([NSJSONSerialization isValidJSONObject:items]) {
        
        // Serialize the array
        json = [NSJSONSerialization dataWithJSONObject:items options:NSJSONWritingPrettyPrinted error:&error];
        
        if (json != nil && error == nil) {
            jsonString = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
        }
    }
    
    return jsonString;
    
}

+ (NSArray *)cartItemsFromJson:(NSString *)jsonString {
    
    NSError *error = nil;
    NSArray *jsonArray = [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options: NSJSONReadingMutableContainers error:&error];
    
    if (!jsonArray) {
        NSLog(@"ACCCustomTagProvider | Error parsing JSON: %@", error);
    }
    
    
    NSMutableArray *items = [[NSMutableArray alloc] init];
    
    [jsonArray enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        
        if (![obj isKindOfClass:[NSDictionary class]]) {
            NSLog(@"ACCCustomTagProvider | Object is not a dictionnary");
            return;
        }

        NSDictionary *item = obj;
        ACCCartItem *cartItem = [[ACCCartItem alloc] init];
        if ([item objectForKey:KEY_CART_ID]) {
            [cartItem setIdentifier:[item objectForKey:KEY_CART_ID]];
        }
        
        if ([item objectForKey:KEY_ITEM_NAME]) {
            [cartItem setName:[item objectForKey:KEY_ITEM_NAME]];
        }
        
        if ([item objectForKey:KEY_ITEM_BRAND]) {
            [cartItem setBrand:[item objectForKey:KEY_ITEM_BRAND]];
        }
        
        if ([item objectForKey:KEY_ITEM_CATEGORY]) {
            [cartItem setCategory:[item objectForKey:KEY_ITEM_CATEGORY]];
        }
        
        if ([item objectForKey:KEY_ITEM_PRICE]) {
            NSNumber *itemPrice = [item objectForKey:KEY_ITEM_PRICE];
            [cartItem setPrice:itemPrice.doubleValue];
        }
        
        if ([item objectForKey:KEY_ITEM_QUANTITY]) {
            NSNumber *itemQuantity = [item objectForKey:KEY_ITEM_QUANTITY];
            [cartItem setQuantity:itemQuantity.integerValue];
        }
        
        [items addObject:cartItem];
        
    }];
    
    return items;
    
}

@end
