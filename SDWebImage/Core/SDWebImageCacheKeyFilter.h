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
 * Block definition for cache key filter.
 * Takes a URL and returns a modified cache key string.
 *
 * @param url The URL to generate a cache key for
 * @return The filtered cache key string
 */
typedef NSString * _Nullable(^SDWebImageCacheKeyFilterBlock)(NSURL * _Nonnull url);

/**
 * Protocol for cache key filtering.
 * Provides a more extensible approach than blocks alone and improves Swift interoperability
 * without requiring @convention(block) annotations.
 */
@protocol SDWebImageCacheKeyFilter <NSObject>

/**
 * Returns a cache key string for the specified URL.
 *
 * @param url The URL to generate a cache key for
 * @return The filtered cache key string
 */
- (nullable NSString *)cacheKeyForURL:(nonnull NSURL *)url;

@end

/**
 * A concrete implementation of SDWebImageCacheKeyFilter using blocks.
 * This class wraps a block-based filter implementation to conform to the protocol.
 */
@interface SDWebImageCacheKeyFilter : NSObject <SDWebImageCacheKeyFilter>

/**
 * The block used for cache key filtering.
 */
@property (nonatomic, copy, readonly) SDWebImageCacheKeyFilterBlock filterBlock;

/**
 * Unavailable initializers - use the designated initializers instead.
 */
- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Initializes a cache key filter with the specified block.
 *
 * @param block The block to use for cache key filtering
 * @return A new cache key filter instance
 */
- (nonnull instancetype)initWithBlock:(nonnull SDWebImageCacheKeyFilterBlock)block NS_DESIGNATED_INITIALIZER;

/**
 * Creates a cache key filter with the specified block.
 * Factory method alternative to the initializer.
 *
 * @param block The block to use for cache key filtering
 * @return A new cache key filter instance
 */
+ (nonnull instancetype)cacheKeyFilterWithBlock:(nonnull SDWebImageCacheKeyFilterBlock)block;

@end

NS_ASSUME_NONNULL_END