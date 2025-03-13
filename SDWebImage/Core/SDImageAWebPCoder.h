/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDImageIOAnimatedCoder.h"

/**
 * This coder is used for Google WebP and Animated WebP(AWebP) image format.
 * Image/IO provides WebP decoding support in iOS 14/macOS 11/tvOS 14/watchOS 7+.
 *
 * @note Currently Image/IO does not support WebP encoding. If you need WebP encoding,
 *       use a custom codec instead.
 * @note If you need to support lower firmware versions for WebP, consider using
 *       https://github.com/SDWebImage/SDWebImageWebPCoder
 */
API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0), watchos(7.0))
@interface SDImageAWebPCoder : SDImageIOAnimatedCoder <SDProgressiveImageCoder, SDAnimatedImageCoder>

/**
 * Returns the shared instance of the WebP coder.
 * This singleton instance can be used across the app.
 */
@property (nonatomic, class, readonly, nonnull) SDImageAWebPCoder *sharedCoder;

@end