//
//  S6Utils.m
//  S6SDK
//
//  Created by pp on 2017/8/29.
//  Copyright © 2017年 pp. All rights reserved.
//

#import "S6Utils.h"
#import "iOSMacro.h"

@implementation S6Utils

+ (NSDictionary *)dictFromChar:(const char *)pChar {
    NSString *str = nil;
    if (pChar) {
        str = S6Char2NSString(pChar);
    }

    NSData *data = [str dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:data
                                                         options:NSJSONReadingMutableContainers|NSJSONReadingMutableLeaves|NSJSONReadingAllowFragments
                                                           error:nil];
    return dict;
}

@end
