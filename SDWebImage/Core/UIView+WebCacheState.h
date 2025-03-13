/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A loading state to manage View Category which contains multiple states.
 * Used for views that can display multiple images like UIImageView with normal and highlighted states.
 *
 * Example usage:
 * @code
 * SDWebImageLoadState *loadState = [self sd_imageLoadStateForKey:@keypath(self, highlightedImage)];
 * NSProgress *highlightedImageProgress = loadState.progress;
 * @endcode
 */
@interface SDWebImageLoadState : NSObject

/**
 * Image loading URL
 */
@property (nonatomic, strong, nullable) NSURL *url;

/**
 * Image loading progress. 
 * The unit count represents the received size and expected size of download.
 */
@property (nonatomic, strong, nullable) NSProgress *progress;

@end

/**
 * These methods are used for WebCache view which have multiple states for image loading,
 * for example, `UIButton` or `UIImageView.highlightedImage`.
 * 
 * It maintains the state container for per-operation, making it possible to control and
 * check each image loading operation's state.
 *
 * @note For developers who want to add SDWebImage View Category support for their own
 * stateful class, learn more on the Wiki.
 */
@interface UIView (WebCacheState)

/**
 * Gets the image loading state container for the specified operation key.
 *
 * @param key Key for identifying the operations
 * @return The image loading state container
 */
- (nullable SDWebImageLoadState *)sd_imageLoadStateForKey:(nullable NSString *)key;

/**
 * Sets the image loading state container for the specified operation key.
 *
 * @param state The image loading state container
 * @param key Key for identifying the operations
 */
- (void)sd_setImageLoadState:(nullable SDWebImageLoadState *)state forKey:(nullable NSString *)key;

/**
 * Removes the image loading state container for the specified operation key.
 *
 * @param key Key for identifying the operations
 */
- (void)sd_removeImageLoadStateForKey:(nullable NSString *)key;

@end

NS_ASSUME_NONNULL_END