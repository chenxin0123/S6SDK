//
//  Macros.h
//  ouyu
//
//  Created by CX on 3/30/16.
//  Copyright © 2016 westcoast. All rights reserved.
//

#ifndef Macros_h
#define Macros_h

#ifdef DEBUG
#define OYLog(format, ...) \
    do { \
        NSLog(@"\n<%@ : %d : %s>-: \n%@", \
        [[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
        __LINE__, \
        __FUNCTION__, \
        [NSString stringWithFormat:format, ##__VA_ARGS__]); \
    } while(0)

#else
    #define OYLog(format, ...) do {} while(0)
#endif

#define S6Char2NSString(c) [NSString stringWithUTF8String:c]

//屏幕常量
#define OYScreenWidth      [[UIScreen mainScreen] bounds].size.width
#define OYScreenHeight     [[UIScreen mainScreen] bounds].size.height

#define OYMakeWeakSelf __weak typeof(self) weakSelf = self;
//显示网络请求错误信息
#ifdef DEBUG
  #define OYShowRequestErrorMsg \
  if (json[@"msg"]) {\
    [FunctionCommon popNotice:json[@"msg"]];\
  }
  #define OYShowRequestFailMsg [FunctionCommon popNotice:@"连接失败！"];
#else
  #define OYShowRequestErrorMsg
  #define OYShowRequestFailMsg
#endif

#define OYUrlWithTrimmedString(str) [NSURL URLWithString:OYTrimmedString(str)]
#define OYTrimmedString(str) [[str rangeOfString:@"http"].location!=NSNotFound?str:[NSString stringWithFormat:@"http://%@",str] stringByReplacingOccurrencesOfString:@" " withString:@""]

//#define OYUrlStringWithTrimmedString(str) [NSURL URLWithString:[[str rangeOfString:@"http"].location!=NSNotFound?str:[NSString stringWithFormat:@"http://%@",str] stringByReplacingOccurrencesOfString:@" " withString:@""]]

#define OYReturnIfNotLogin \
if (!OY_IsLogin) { \
    return; \
}

#define OY_IsLogin [[PersonalManager shareInstance] isLogin]

#define OYPushLoginVC \
do{\
UIViewController *loginViewController = [[NSClassFromString(@"OYLoginViewController") alloc] init];\
[self.navigationController pushViewController:loginViewController animated:YES];\
}while(0);

#define OYLoginRequired(...) if ([[PersonalManager shareInstance] isLogin]) {\
__VA_ARGS__\
}else{ OYPushLoginVC }

#define OYNavPush(VC) do{VC *vc = [VC new]; \
[self.navigationController pushViewController:vc animated:YES];}while(0)

//APP代理
#define OYAppDelegate [UIApplication sharedApplication].delegate
//APP根控制器
#define OYAppRootController [[[UIApplication sharedApplication] keyWindow] rootViewController]

///注册与发送通知
#define OYPostNoti(NAME,OBJECT,USERINFO) \
[[NSNotificationCenter defaultCenter] postNotificationName:NAME object:OBJECT userInfo:USERINFO]
#define OYObserveNoti(OBSERVER,SELECTEOR,NAME,OBJECT) \
[[NSNotificationCenter defaultCenter] addObserver:OBSERVER selector:@selector(SELECTEOR) name:NAME object:OBJECT]
#define OYRemoveNoti(NotiName) [[NSNotificationCenter defaultCenter]removeObserver:self name:NotiName object:nil];
#define OYRemoveAllNoti [[NSNotificationCenter defaultCenter] removeObserver:self];

//文件目录
#define OYDocFolder OYDocumentDirectory(@"OYDocuments")
#define OYCreateAndExcludedFromBackup(path) \
do{ \
if (![[NSFileManager defaultManager] fileExistsAtPath:path]) { \
[[NSFileManager defaultManager] createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:nil]; \
NSURL *url = [NSURL fileURLWithPath:path]; \
NSError *error; \
BOOL success = [url setResourceValue:[NSNumber numberWithBool:YES] forKey:NSURLIsExcludedFromBackupKey error:&error]; \
if (!success || error) { \
OYLog(@"set NSURLIsExcludedFromBackupKey error: %@",error.userInfo); \
} else { \
OYLog(@"set NSURLIsExcludedFromBackupKey success"); \
} \
} \
}while(0);


#define OYDocumentDirectory(path) ([[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingPathComponent:path])
#define OYCacheDirectory(path) ([[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingPathComponent:path])

#define OYUID ([PersonalManager shareInstance].uid)
#define CITY_ID [[CityManager shareInstance] getCurrentCityID]

//画单个像素的线的时候使用的宏
#define OYSingleLineWidth           (1 / [UIScreen mainScreen].scale)
#define OYSingleLineOffset   ((1 / [UIScreen mainScreen].scale) / 2)


#define OYString(_number_) (_number_?[NSString stringWithFormat:@"%@",_number_]:nil) //number转换为字符串
#define OYIsValidString(STR) (STR&&[STR isKindOfClass:[NSString class]]&&![STR isEqualToString:@""])
#define OYIsValidObject(OBJ) (OBJ&&![OBJ isKindOfClass:[NSNull class]])
#define OYStringIsEqual(str1,str2) [str1 isEqualToString:str2]

//安全的给字典设置值 防止crash
#define OYSetKeyValuePair(DICT,KEY,VALUE) if(OYIsValidObject(VALUE)&&OYIsValidObject(KEY)) DICT[KEY] = VALUE;

//系统版本
#define OYDeviceVersionGreaterThanOrEqualTo(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)

//执行block
#define OYExecuteBlock(bolck, ...)  if (bolck) { bolck(__VA_ARGS__); }
#endif /* Macros_h */
