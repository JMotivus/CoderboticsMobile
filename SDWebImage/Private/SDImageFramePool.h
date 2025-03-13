/*
* This file is part of the SDWebImage package.
* (c) Olivier Poitrey <rs@dailymotion.com>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"
#import "SDImageCoder.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A per-provider frame pool that manages animated image frames.
 * Each player using the same provider shares the same frame buffer.
 * This allows for efficient memory usage when multiple views display the same animated image.
 */
@interface SDImageFramePool : NSObject

/**
 * Registers a provider with the frame pool and increases its reference count.
 * @param provider The animated image provider to register
 * @return The frame pool instance
 */
+ (instancetype)registerProvider:(id<SDAnimatedImageProvider>)provider;

/**
 * Unregisters a provider from the frame pool and decreases its reference count.
 * When the reference count reaches zero, the frame pool is deallocated.
 * @param provider The animated image provider to unregister
 */
+ (void)unregisterProvider:(id<SDAnimatedImageProvider>)provider;

/**
 * Prefetches the frame at the specified index.
 * Caller should use `frameAtIndex:` to check if prefetching has completed.
 * @param index The index of the frame to prefetch
 */
- (void)prefetchFrameAtIndex:(NSUInteger)index;

/**
 * Maximum number of frames to keep in the buffer.
 * Used to balance RAM usage and CPU performance.
 * Default is unlimited (0).
 */
@property (nonatomic, assign) NSUInteger maxBufferCount;

/**
 * Maximum number of concurrent frame fetch operations.
 * Used to balance CPU load.
 * Default is 1.
 */
@property (nonatomic, assign) NSUInteger maxConcurrentCount;

/**
 * The current number of frames in the pool.
 */
@property (nonatomic, readonly) NSUInteger currentFrameCount;

/**
 * Retrieves the frame at the specified index.
 * @param index The index of the frame to retrieve
 * @return The frame at the specified index, or nil if not available
 */
- (nullable UIImage *)frameAtIndex:(NSUInteger)index;

/**
 * Sets a frame at the specified index.
 * @param frame The frame to set
 * @param index The index at which to set the frame
 */
- (void)setFrame:(nullable UIImage *)frame atIndex:(NSUInteger)index;

/**
 * Removes the frame at the specified index.
 * @param index The index of the frame to remove
 */
- (void)removeFrameAtIndex:(NSUInteger)index;

/**
 * Removes all frames from the pool.
 */
- (void)removeAllFrames;

@end

NS_ASSUME_NONNULL_END