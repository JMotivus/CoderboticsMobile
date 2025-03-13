/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * UIImage category that provides force decode functionality to avoid Image/IO's lazy decoding
 * during rendering, which can improve performance by pre-decoding images.
 */
@interface UIImage (ForceDecode)

/**
 * A boolean value indicating whether the image has already been decoded.
 * This property helps avoid redundant force decoding operations.
 *
 * Force decoding is used in two scenarios:
 * 1. For images created with ImageIO (via `CGImageCreateWithImageSource` SPI), which use lazy decoding,
 *    we trigger the decode before rendering to improve performance
 * 2. For images created without ImageIO (via `CGImageCreate` API), we ensure proper memory alignment
 *    for efficient rendering by CoreAnimation without additional copying
 *
 * @note For coder plugin developers, always use SDImageCoderHelper's `colorSpaceGetDeviceRGB`/`preferredPixelFormat` 
 *       to create CGImage instances.
 * @note For more information about force decoding benefits, see: https://github.com/path/FastImageCache#byte-alignment
 * @note From v5.17.0, the default value is always NO. Use `SDImageForceDecodePolicy` to control more complex policies.
 */
@property (nonatomic, assign) BOOL sd_isDecoded;

/**
 * Decodes the provided image to improve rendering performance.
 *
 * @param image The image to be decoded
 * @return The decoded image, or nil if the input was nil
 */
+ (nullable UIImage *)sd_decodedImageWithImage:(nullable UIImage *)image;

/**
 * Decodes and scales down the provided image to reduce memory usage while maintaining quality.
 *
 * @param image The image to be decoded and scaled down
 * @return The decoded and scaled down image, or nil if the input was nil
 */
+ (nullable UIImage *)sd_decodedAndScaledDownImageWithImage:(nullable UIImage *)image;

/**
 * Decodes and scales down the provided image with a specified memory limit.
 * 
 * @param image The image to be decoded and scaled down
 * @param bytes The maximum memory size in bytes. Specify 0 to use the built-in default limit.
 * @return The decoded and scaled down image, or nil if the input was nil
 */
+ (nullable UIImage *)sd_decodedAndScaledDownImageWithImage:(nullable UIImage *)image limitBytes:(NSUInteger)bytes;

@end

NS_ASSUME_NONNULL_END