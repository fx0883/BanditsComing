//
//  AdmobManager.h
//  PuzzleGame
//
//  Created by fx on 14/10/27.
//  Copyright (c) 2014年 FS. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GoogleMobileAds/GADBannerView.h>
#import <GoogleMobileAds/GADRequest.h>
#import <StoreKit/StoreKit.h>
#import <GoogleMobileAds/GADInterstitial.h>


// 单例
#undef	AS_SINGLETON
#define AS_SINGLETON( __class ) \
+ (__class *)sharedInstance;

#undef	DEF_SINGLETON
#define DEF_SINGLETON( __class ) \
+ (__class *)sharedInstance \
{ \
static dispatch_once_t once; \
static __class * __singleton__; \
dispatch_once( &once, ^{ __singleton__ = [[__class alloc] init]; } ); \
return __singleton__; \
}


#define XS_INITCLASS( __class ) [[__class alloc] init];


#define KADMOBSTATECHANGE @"kAdmobStateChange"

@interface AdmobManager : NSObject<GADBannerViewDelegate,GADInterstitialDelegate>
{

}


/*!
 *  单例宏的调用
 */
AS_SINGLETON(AdmobManager)

@property(nonatomic, strong) GADBannerView *bannerView;
@property(nonatomic, strong) UIViewController *rootViewController;
@property(readwrite) BOOL bIsBannerViewReady;

@property (nonatomic, strong) GADInterstitial *adInterstitial;
@property(nonatomic,strong) UIViewController *curControlView;
@property(readwrite) BOOL bIsFirstGADInterstitial;

@property (readwrite) CGFloat floatBannerWidth;
@property (readwrite) CGFloat floatBannerHeight;

//CGFloat _floatBannerHeight;
//CGFloat _floatBannerWidth;
-(instancetype)initWithViewController:(UIViewController*)rootViewController;
-(void)startInterstitialView;
@end
