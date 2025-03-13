/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"
#import "NSData+ImageContentType.h"

/**
 * UIImage category for convenient image format decoding/encoding.
 * Provides methods to create images from data and convert images to data
 * with support for various formats, scaling, and animation control.
 */
@interface UIImage (MultiFormat)

#pragma mark - Decode Methods

/**
 * Create and decode an image with the specified image data.
 *
 * @param data The image data
 * @return The created image, or nil if data is invalid
 */
+ (nullable UIImage *)sd_imageWithData:(nullable NSData *)data;

/**
 * Create and decode an image with the specified image data and scale.
 * 
 * @param data The image data
 * @param scale The image scale factor. Should be greater than or equal to 1.0
 * @return The created image, or nil if data is invalid
 */
+ (nullable UIImage *)sd_imageWithData:(nullable NSData *)data scale:(CGFloat)scale;

/**
 * Create and decode an image with the specified image data and scale, with animation control.
 * 
 * @param data The image data
 * @param scale The image scale factor. Should be greater than or equal to 1.0
 * @param firstFrameOnly If YES, decode only the first frame as static image even for animated formats
 * @return The created image, or nil if data is invalid
 */
+ (nullable UIImage *)sd_imageWithData:(nullable NSData *)data
                                 scale:(CGFloat)scale
                         firstFrameOnly:(BOOL)firstFrameOnly;

#pragma mark - Encode Methods

/**
 * Encode the current image to data, with automatic format detection.
 *
 * @note If the receiver is `SDAnimatedImage`, this will return the animated image data if available.
 *       No additional encoding process will be performed.
 * @note For macOS, if the receiver contains only `SDAnimatedImageRep`, this will return the animated
 *       image data if available. No additional encoding process will be performed.
 * @return The encoded data, or nil if encoding fails
 */
- (nullable NSData *)sd_imageData;

/**
 * Encode the current image to data with the specified image format.
 *
 * @param imageFormat The desired image format for encoding
 * @return The encoded data, or nil if encoding fails
 */
- (nullable NSData *)sd_imageDataAsFormat:(SDImageFormat)imageFormat NS_SWIFT_NAME(sd_imageData(as:));

/**
 * Encode the current image to data with the specified image format and compression quality.
 *
 * @param imageFormat The desired image format for encoding
 * @param compressionQuality The quality of the resulting image data (0.0-1.0)
 *                           Some coders may not support compression quality
 * @return The encoded data, or nil if encoding fails
 */
- (nullable NSData *)sd_imageDataAsFormat:(SDImageFormat)imageFormat
                       compressionQuality:(double)compressionQuality
                       NS_SWIFT_NAME(sd_imageData(as:compressionQuality:));

/**
 * Encode the current image to data with the specified image format, compression quality,
 * and animation control.
 *
 * @param imageFormat The desired image format for encoding
 * @param compressionQuality The quality of the resulting image data (0.0-1.0)
 *                           Some coders may not support compression quality
 * @param firstFrameOnly If YES, encode only the first frame as static image even for animated images
 * @return The encoded data, or nil if encoding fails
 */
- (nullable NSData *)sd_imageDataAsFormat:(SDImageFormat)imageFormat
                       compressionQuality:(double)compressionQuality
                           firstFrameOnly:(BOOL)firstFrameOnly
                       NS_SWIFT_NAME(sd_imageData(as:compressionQuality:firstFrameOnly:));

@end