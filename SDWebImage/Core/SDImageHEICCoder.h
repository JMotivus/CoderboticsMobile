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
 * This coder is used for HEIC (HEIF with HEVC container codec) image format.
 * 
 * Supported features:
 * - Static HEIC (.heic): iOS 11/macOS 10.13/tvOS 11/watchOS 4+
 * - Animated HEIC (.heics): iOS 13/macOS 10.15/tvOS 13/watchOS 6+
 * 
 * For more information about the HEIC standard, see:
 * https://nokiatech.github.io/heif/technical.html
 * 
 * @note This coder is not included in the default coder list because:
 *       1. HEIC animated images are rare
 *       2. Apple's implementation has known performance issues
 *       Enable this coder explicitly if needed.
 * 
 * @note For HEIF support on lower firmware versions, consider using:
 *       https://github.com/SDWebImage/SDWebImageHEIFCoder
 */
API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0))
@interface SDImageHEICCoder : SDImageIOAnimatedCoder <SDProgressiveImageCoder, SDAnimatedImageCoder>

/**
 * Returns the shared instance of the HEIC coder.
 * This singleton instance can be used across the app.
 */
@property (nonatomic, class, readonly, nonnull) SDImageHEICCoder *sharedCoder;

@end