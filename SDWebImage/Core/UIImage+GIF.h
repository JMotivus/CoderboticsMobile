/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 * (c) Laurin Brandner
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * This category provides a convenience method for creating UIImage instances from GIF data.
 * For more detailed control, use methods in `UIImage+MultiFormat.h` or directly use `SDImageCoder`.
 */
@interface UIImage (GIF)

/**
 * Creates a UIImage from GIF data.
 * This method handles both animated and static GIF formats:
 * - For animated GIF data, it creates an animated UIImage
 * - For static GIF data, it creates a static UIImage
 *
 * @param data The GIF data to create an image from
 * @return A UIImage created from the GIF data, or nil if creation fails
 */
+ (nullable UIImage *)sd_imageWithGIFData:(nullable NSData *)data;

@end

NS_ASSUME_NONNULL_END