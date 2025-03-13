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
 * Block definition for cache serialization.
 * @param image The loaded image to be serialized
 * @param data The original loaded image data (may be nil for transformed images)
 * @param imageURL The URL of the image
 * @return The serialized data to be stored in disk cache
 */
typedef NSData * _Nullable(^SDWebImageCacheSerializerBlock)(UIImage * _Nonnull image, NSData * _Nullable data, NSURL * _Nullable imageURL);

/**
 * Protocol for cache serializer.
 * This protocol makes the serialization process extensible and allows Swift users
 * to implement it without needing to use `@convention(block)` to store blocks in context options.
 */
@protocol SDWebImageCacheSerializer <NSObject>

/**
 * Provides the image data to be stored in disk cache
 * @param image The loaded image
 * @param data The original loaded image data. May be nil when image is transformed (UIImage.sd_isTransformed = YES)
 * @param imageURL The image URL
 * @return The data to be stored in disk cache
 */
- (nullable NSData *)cacheDataWithImage:(nonnull UIImage *)image 
                           originalData:(nullable NSData *)data 
                               imageURL:(nullable NSURL *)imageURL;

@end

/**
 * A concrete implementation of SDWebImageCacheSerializer using blocks.
 * This class wraps a block-based serializer in the protocol interface.
 */
@interface SDWebImageCacheSerializer : NSObject <SDWebImageCacheSerializer>

/**
 * Creates a cache serializer with the specified block.
 * @param block The serializer block to use
 * @return A new cache serializer instance
 */
+ (nonnull instancetype)cacheSerializerWithBlock:(nonnull SDWebImageCacheSerializerBlock)block;

/**
 * Initializes a cache serializer with the specified block.
 * @param block The serializer block to use
 * @return A new cache serializer instance
 */
- (nonnull instancetype)initWithBlock:(nonnull SDWebImageCacheSerializerBlock)block;

/**
 * Default initializers are unavailable. Use the block-based initializers instead.
 */
- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;

@end