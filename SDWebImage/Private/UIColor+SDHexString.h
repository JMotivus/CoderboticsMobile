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
 * UIColor category that provides hex string conversion functionality
 */
@interface UIColor (SDHexString)

/**
 * Convenience way to get hex string from color.
 * @return A 32-bit RGBA hex string representation of the color (e.g. "#00000000")
 */
@property (nonatomic, copy, readonly) NSString *sd_hexString;

@end

NS_ASSUME_NONNULL_END