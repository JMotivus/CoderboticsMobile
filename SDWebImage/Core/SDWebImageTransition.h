/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

#if SD_UIKIT || SD_MAC
#import "SDImageCache.h"

#if SD_UIKIT
typedef UIViewAnimationOptions SDWebImageAnimationOptions;
#else
/**
 * Animation options for macOS transitions
 */
typedef NS_OPTIONS(NSUInteger, SDWebImageAnimationOptions) {
    // Context options
    SDWebImageAnimationOptionAllowsImplicitAnimation   = 1 << 0, // specify `allowsImplicitAnimation` for the `NSAnimationContext`
    
    // Timing curve options
    SDWebImageAnimationOptionCurveEaseInOut            = 0 << 16, // default
    SDWebImageAnimationOptionCurveEaseIn               = 1 << 16,
    SDWebImageAnimationOptionCurveEaseOut              = 2 << 16,
    SDWebImageAnimationOptionCurveLinear               = 3 << 16,
    
    // Transition style options
    SDWebImageAnimationOptionTransitionNone            = 0 << 20, // default
    SDWebImageAnimationOptionTransitionFlipFromLeft    = 1 << 20,
    SDWebImageAnimationOptionTransitionFlipFromRight   = 2 << 20,
    SDWebImageAnimationOptionTransitionCurlUp          = 3 << 20,
    SDWebImageAnimationOptionTransitionCurlDown        = 4 << 20,
    SDWebImageAnimationOptionTransitionCrossDissolve   = 5 << 20,
    SDWebImageAnimationOptionTransitionFlipFromTop     = 6 << 20,
    SDWebImageAnimationOptionTransitionFlipFromBottom  = 7 << 20,
};
#endif

/**
 * Block type for transition preparation before animation
 */
typedef void (^SDWebImageTransitionPreparesBlock)(__kindof UIView * _Nonnull view, UIImage * _Nullable image, NSData * _Nullable imageData, SDImageCacheType cacheType, NSURL * _Nullable imageURL);

/**
 * Block type for transition animations
 */
typedef void (^SDWebImageTransitionAnimationsBlock)(__kindof UIView * _Nonnull view, UIImage * _Nullable image);

/**
 * Block type for transition completion
 */
typedef void (^SDWebImageTransitionCompletionBlock)(BOOL finished);

/**
 * This class provides transition animations after image loading completes.
 * Use with `sd_imageTransition` in UIView+WebCache.h
 *
 * For UIKit (iOS & tvOS), we use `+[UIView transitionWithView:duration:options:animations:completion]`.
 * For AppKit (macOS), we use `+[NSAnimationContext runAnimationGroup:completionHandler:]`.
 * You can call `+[NSAnimationContext currentContext]` to access the context during animations.
 *
 * @note These transitions are for basic usage. For complex animations, consider using
 * Core Animation directly or use `SDWebImageAvoidAutoSetImage` and implement your own
 * animation after image loading completes.
 */
@interface SDWebImageTransition : NSObject

/**
 * By default, we set the image to the view at the beginning of the animations.
 * Set to YES to disable this behavior and provide custom image setting logic.
 */
@property (nonatomic, assign) BOOL avoidAutoSetImage;

/**
 * The duration of the transition animation in seconds. Defaults to 0.5.
 */
@property (nonatomic, assign) NSTimeInterval duration;

/**
 * The timing function for all animations within this transition (macOS only).
 * @deprecated Use SDWebImageAnimationOptions instead, or modify NSAnimationContext.currentContext
 */
@property (nonatomic, strong, nullable) CAMediaTimingFunction *timingFunction API_UNAVAILABLE(ios, tvos, watchos) API_DEPRECATED("Use SDWebImageAnimationOptions instead, or grab NSAnimationContext.currentContext and modify the timingFunction", macos(10.10, 10.10));

/**
 * Options controlling how the animations are performed.
 */
@property (nonatomic, assign) SDWebImageAnimationOptions animationOptions;

/**
 * Block executed before the animation sequence starts.
 */
@property (nonatomic, copy, nullable) SDWebImageTransitionPreparesBlock prepares;

/**
 * Block containing the changes to make to the specified view during animation.
 */
@property (nonatomic, copy, nullable) SDWebImageTransitionAnimationsBlock animations;

/**
 * Block executed when the animation sequence ends.
 */
@property (nonatomic, copy, nullable) SDWebImageTransitionCompletionBlock completion;

@end

/**
 * Convenience methods to create common transition effects.
 *
 * For UIKit, these transitions use the corresponding `animationOptions`.
 * By default, `UIViewAnimationOptionAllowUserInteraction` is enabled to allow user interaction during transitions.
 *
 * For AppKit, these transitions use Core Animation in the `animations` block.
 * Your view must be layer-backed - set `wantsLayer = YES` before applying transitions.
 */
@interface SDWebImageTransition (Conveniences)

/// Fade-in transition
@property (nonatomic, class, nonnull, readonly) SDWebImageTransition *fadeTransition;

/// Flip from left transition
@property (nonatomic, class, nonnull, readonly) SDWebImageTransition *flipFromLeftTransition;

/// Flip from right transition
@property (nonatomic, class, nonnull, readonly) SDWebImageTransition *flipFromRightTransition;

/// Flip from top transition
@property (nonatomic, class, nonnull, readonly) SDWebImageTransition *flipFromTopTransition;

/// Flip from bottom transition
@property (nonatomic, class, nonnull, readonly) SDWebImageTransition *flipFromBottomTransition;

/// Curl up transition
@property (nonatomic, class, nonnull, readonly) SDWebImageTransition *curlUpTransition;

/// Curl down transition
@property (nonatomic, class, nonnull, readonly) SDWebImageTransition *curlDownTransition;

/**
 * Creates a fade-in transition with the specified duration.
 * @param duration The transition duration (uses ease-in-out timing)
 * @return A configured transition object
 */
+ (nonnull instancetype)fadeTransitionWithDuration:(NSTimeInterval)duration NS_SWIFT_NAME(fade(duration:));

/**
 * Creates a flip-from-left transition with the specified duration.
 * @param duration The transition duration (uses ease-in-out timing)
 * @return A configured transition object
 */
+ (nonnull instancetype)flipFromLeftTransitionWithDuration:(NSTimeInterval)duration NS_SWIFT_NAME(flipFromLeft(duration:));

/**
 * Creates a flip-from-right transition with the specified duration.
 * @param duration The transition duration (uses ease-in-out timing)
 * @return A configured transition object
 */
+ (nonnull instancetype)flipFromRightTransitionWithDuration:(NSTimeInterval)duration NS_SWIFT_NAME(flipFromRight(duration:));

/**
 * Creates a flip-from-top transition with the specified duration.
 * @param duration The transition duration (uses ease-in-out timing)
 * @return A configured transition object
 */
+ (nonnull instancetype)flipFromTopTransitionWithDuration:(NSTimeInterval)duration NS_SWIFT_NAME(flipFromTop(duration:));

/**
 * Creates a flip-from-bottom transition with the specified duration.
 * @param duration The transition duration (uses ease-in-out timing)
 * @return A configured transition object
 */
+ (nonnull instancetype)flipFromBottomTransitionWithDuration:(NSTimeInterval)duration NS_SWIFT_NAME(flipFromBottom(duration:));

/**
 * Creates a curl-up transition with the specified duration.
 * @param duration The transition duration (uses ease-in-out timing)
 * @return A configured transition object
 */
+ (nonnull instancetype)curlUpTransitionWithDuration:(NSTimeInterval)duration NS_SWIFT_NAME(curlUp(duration:));

/**
 * Creates a curl-down transition with the specified duration.
 * @param duration The transition duration (uses ease-in-out timing)
 * @return A configured transition object
 */
+ (nonnull instancetype)curlDownTransitionWithDuration:(NSTimeInterval)duration NS_SWIFT_NAME(curlDown(duration:));

@end

#endif