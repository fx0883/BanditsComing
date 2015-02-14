//
//  AdmobManager.m
//  PuzzleGame
//
//  Created by fx on 14/10/27.
//  Copyright (c) 2014年 FS. All rights reserved.
//
#define MY_BANNER_UNIT_ID @"ca-app-pub-5934917937656240/6752496410" //@"a1531d79701df01"

#define MY_BANNER_INTERSTITIAL_ID @"ca-app-pub-5934917937656240/8229229611" //
#import "AdmobManager.h"
//#import "HMIAPHelper.h"


@implementation AdmobManager

DEF_SINGLETON(AdmobManager)


-(instancetype)init
{
    self = [super init];
    if (self) {
        
//        if (![SharedIAP hasRemovedAds])
        {
            [self loadAdmobManagerDefaultConfig];
          //  [self loadBannerView];
            [self loadInterstitial];
        }   
    }
    return self;
}


-(instancetype)initWithViewController:(UIViewController*)rootViewController
{
    self = [super init];
    if (self) {
        self.rootViewController = rootViewController;
        [self loadBannerView];
        [self loadInterstitial];
        self.curControlView  =rootViewController;
    }
    return self;
}

-(void)loadAdmobManagerDefaultConfig
{
    self.rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    self.curControlView = [UIApplication sharedApplication].keyWindow.rootViewController;
//    if (self.curControlView == nil) {
//        self.curControlView = [UIViewController new];
//        UIWindow *window =[UIApplication sharedApplication].keyWindow;
//        
//        int k=0;
//        k++;
//    }
    self.bIsBannerViewReady = NO;
    self.bIsFirstGADInterstitial = YES;
}

-(void)loadBannerView
{
    //loadBannerConfig
    _floatBannerWidth = [UIScreen mainScreen].bounds.size.width;
    _floatBannerHeight = 50.0;
    
    
    self.bannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerPortrait];
    
    
    
    // Replace this ad unit ID with your own ad unit ID.
    self.bannerView.adUnitID = MY_BANNER_UNIT_ID;
    self.bannerView.rootViewController =self.rootViewController;
    self.bannerView.delegate = self;
    
    GADRequest *request = [GADRequest request];
    // Requests test ads on devices you specify. Your test device ID is printed to the console when
    // an ad request is made.
    request.testDevices = @[
                            @"2077ef9a63d2b398840261c8221a0c9a"  // Eric's iPod Touch
                            ];
    [self.bannerView loadRequest:request];
    
}


#pragma mark- Ad Request Lifecycle Notifications

/// Called when an ad request loaded an ad. This is a good opportunity to add this view to the
/// hierarchy if it has not been added yet. If the ad was received as a part of the server-side auto
/// refreshing, you can examine the hasAutoRefreshed property of the view.
- (void)adViewDidReceiveAd:(GADBannerView *)view
{
    self.bIsBannerViewReady = YES;
    NSLog(@"adViewDidReceiveAd =========");
    
    
   
    

    

}

/// Called when an ad request failed. Normally this is because no network connection was available
/// or no ads were available (i.e. no fill). If the error was received as a part of the server-side
/// auto refreshing, you can examine the hasAutoRefreshed property of the view.
- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    //[self loadBannerView];
}

#pragma mark- Click-Time Lifecycle Notifications

/// Called just before presenting the user a full screen view, such as a browser, in response to
/// clicking on an ad. Use this opportunity to stop animations, time sensitive interactions, etc.
///
/// Normally the user looks at the ad, dismisses it, and control returns to your application by
/// calling adViewDidDismissScreen:. However if the user hits the Home button or clicks on an App
/// Store link your application will end. On iOS 4.0+ the next method called will be
/// applicationWillResignActive: of your UIViewController
/// (UIApplicationWillResignActiveNotification). Immediately after that adViewWillLeaveApplication:
/// is called.
- (void)adViewWillPresentScreen:(GADBannerView *)adView
{
    
}

/// Called just before dismissing a full screen view.
- (void)adViewWillDismissScreen:(GADBannerView *)adView
{
    
}

/// Called just after dismissing a full screen view. Use this opportunity to restart anything you
/// may have stopped as part of adViewWillPresentScreen:.
- (void)adViewDidDismissScreen:(GADBannerView *)adView
{
    
}

/// Called just before the application will background or terminate because the user clicked on an
/// ad that will launch another application (such as the App Store). The normal
/// UIApplicationDelegate methods, like applicationDidEnterBackground:, will be called immediately
/// before this.
- (void)adViewWillLeaveApplication:(GADBannerView *)adView
{
    
}





#pragma mark- GADInterstitial

-(void)loadInterstitial {
    _adInterstitial = [[GADInterstitial alloc] init];
    _adInterstitial.adUnitID = MY_BANNER_INTERSTITIAL_ID;
    _adInterstitial.delegate = self;
    
    GADRequest *request = [GADRequest request];
    request.testDevices = @[
                            @"2077ef9a63d2b398840261c8221a0c9a"  // Eric's iPod Touch
                            ];
    [_adInterstitial loadRequest:request];
}


#pragma mark Ad Request Lifecycle Notifications

/// Called when an interstitial ad request succeeded. Show it at the next transition point in your
/// application such as when transitioning between view controllers.
- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
//    if (self.bIsFirstGADInterstitial == YES) {
//        self.bIsFirstGADInterstitial = NO;
//        [self startInterstitialView];
//    }
//    else
    {
        [[NSNotificationCenter defaultCenter] postNotificationName:KADMOBSTATECHANGE object: [NSNumber numberWithBool:YES]];
    }
    NSLog(@"interstitialDidReceiveAd =========");

}

/// Called when an interstitial ad request completed without an interstitial to
/// show. This is common since interstitials are shown sparingly to users.
- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error
{
    [self loadInterstitial];
}

#pragma mark Display-Time Lifecycle Notifications

/// Called just before presenting an interstitial. After this method finishes the interstitial will
/// animate onto the screen. Use this opportunity to stop animations and save the state of your
/// application in case the user leaves while the interstitial is on screen (e.g. to visit the App
/// Store from a link on the interstitial).
- (void)interstitialWillPresentScreen:(GADInterstitial *)ad
{
    
}

/// Called before the interstitial is to be animated off the screen.
- (void)interstitialWillDismissScreen:(GADInterstitial *)ad
{
    
}

/// Called just after dismissing an interstitial and it has animated off the screen.
- (void)interstitialDidDismissScreen:(GADInterstitial *)ad
{
    [self loadInterstitial];
}

/// Called just before the application will background or terminate because the user clicked on an
/// ad that will launch another application (such as the App Store). The normal
/// UIApplicationDelegate methods, like applicationDidEnterBackground:, will be called immediately
/// before this.
- (void)interstitialWillLeaveApplication:(GADInterstitial *)ad
{
    
}

-(void)startInterstitialView
{
    if (self.curControlView != nil)
    {
        [self playAgainAdWithVC:self.curControlView];
    }
}

- (void)playAgainAdWithVC:(UIViewController*)viewController
{
    if (_adInterstitial.isReady) {
        [_adInterstitial presentFromRootViewController:viewController];
        [[NSNotificationCenter defaultCenter] postNotificationName:KADMOBSTATECHANGE object: [NSNumber numberWithBool:NO]];
    }
}

-(void)giveMeRate
{
//    [Appirater setAppId:@"909949742"];
//    [Appirater setDaysUntilPrompt:5];
//    [Appirater setUsesUntilPrompt:0];
//    [Appirater setSignificantEventsUntilPrompt:-1];
//    [Appirater setTimeBeforeReminding:2];
//    [Appirater setDebug:YES];
//    [Appirater appLaunched:YES];
    
    
}

@end
