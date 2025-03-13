/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

#if SD_UIKIT || SD_MAC

/**
 * A protocol to customize the indicator during image loading.
 * All methods are called from the main queue.
 */
@protocol SDWebImageIndicator <NSObject>

@required
/**
 * The view associated with the indicator.
 *
 * @return The indicator view
 */
@property (nonatomic, strong, readonly, nonnull) UIView *indicatorView;

/**
 * Start animating the indicator.
 */
- (void)startAnimatingIndicator;

/**
 * Stop animating the indicator.
 */
- (void)stopAnimatingIndicator;

@optional
/**
 * Update the loading progress for the indicator.
 * 
 * @param progress The progress value between 0 and 1.0
 */
- (void)updateIndicatorProgress:(double)progress;

@end

#pragma mark - Activity Indicator

/**
 * Activity indicator class.
 * - For UIKit (iOS/tvOS), it uses a `UIActivityIndicatorView`
 * - For AppKit (macOS), it uses a `NSProgressIndicator` with the spinning style
 */
@interface SDWebImageActivityIndicator : NSObject <SDWebImageIndicator>

#if SD_UIKIT
@property (nonatomic, strong, readonly, nonnull) UIActivityIndicatorView *indicatorView;
#else
@property (nonatomic, strong, readonly, nonnull) NSProgressIndicator *indicatorView;
#endif

@end

/**
 * Convenience methods to create and use activity indicators.
 */
@interface SDWebImageActivityIndicator (Conveniences)

#if !SD_VISION
/// These indicators use fixed colors without dark mode support
/// Gray-style activity indicator
@property (nonatomic, class, nonnull, readonly) SDWebImageActivityIndicator *grayIndicator;
/// Large gray-style activity indicator
@property (nonatomic, class, nonnull, readonly) SDWebImageActivityIndicator *grayLargeIndicator;
/// White-style activity indicator
@property (nonatomic, class, nonnull, readonly) SDWebImageActivityIndicator *whiteIndicator;
/// Large white-style activity indicator
@property (nonatomic, class, nonnull, readonly) SDWebImageActivityIndicator *whiteLargeIndicator;
#endif

/// These indicators use the system style, supporting dark mode if available (iOS 13+/macOS 10.14+)
/// Large activity indicator
@property (nonatomic, class, nonnull, readonly) SDWebImageActivityIndicator *largeIndicator;
/// Medium activity indicator
@property (nonatomic, class, nonnull, readonly) SDWebImageActivityIndicator *mediumIndicator;

@end

#pragma mark - Progress Indicator

/**
 * Progress indicator class.
 * - For UIKit (iOS/tvOS), it uses a `UIProgressView`
 * - For AppKit (macOS), it uses a `NSProgressIndicator` with the bar style
 */
@interface SDWebImageProgressIndicator : NSObject <SDWebImageIndicator>

#if SD_UIKIT
@property (nonatomic, strong, readonly, nonnull) UIProgressView *indicatorView;
#else
@property (nonatomic, strong, readonly, nonnull) NSProgressIndicator *indicatorView;
#endif

@end

/**
 * Convenience methods to create progress indicators.
 * Note: Remember to specify the indicator width or use layout constraints if needed.
 */
@interface SDWebImageProgressIndicator (Conveniences)

/// Default-style progress indicator
@property (nonatomic, class, nonnull, readonly) SDWebImageProgressIndicator *defaultIndicator;

#if SD_UIKIT
/// Bar-style progress indicator (not available on tvOS)
@property (nonatomic, class, nonnull, readonly) SDWebImageProgressIndicator *barIndicator API_UNAVAILABLE(tvos);
#endif

@end

#endif