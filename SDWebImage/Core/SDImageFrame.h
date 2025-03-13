/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"

/**
 * This class represents a single frame in an animated image sequence.
 * Used for creating animated images via `animatedImageWithFrames` in `SDImageCoderHelper`.
 *
 * @note If you need to specify animated images loop count, use `sd_imageLoopCount` 
 * property in `UIImage+Metadata.h`.
 */
@interface SDImageFrame : NSObject

/**
 * The image of current frame. You should not set an animated image.
 */
@property (nonatomic, strong, readonly, nonnull) UIImage *image;

/**
 * The duration of current frame to be displayed in seconds.
 * This value should not be zero.
 */
@property (nonatomic, readonly, assign) NSTimeInterval duration;

/**
 * Create a frame instance with specified image and duration.
 *
 * @param image Current frame's image (must not be nil)
 * @param duration Current frame's duration in seconds (should be positive)
 * @return A new frame instance
 */
+ (nonnull instancetype)frameWithImage:(nonnull UIImage *)image duration:(NSTimeInterval)duration;

/**
 * Initialize a frame instance with specified image and duration.
 *
 * @param image Current frame's image (must not be nil)
 * @param duration Current frame's duration in seconds (should be positive)
 * @return An initialized frame instance
 */
- (nonnull instancetype)initWithImage:(nonnull UIImage *)image duration:(NSTimeInterval)duration;

/**
 * Unavailable initializers
 */
- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;

@end