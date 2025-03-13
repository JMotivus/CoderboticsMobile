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
 * Built in coder using ImageIO that supports APNG encoding/decoding.
 * APNG (Animated Portable Network Graphics) is an extension to the PNG format
 * that allows for animated images similar to GIF but with better quality.
 */
@interface SDImageAPNGCoder : SDImageIOAnimatedCoder <SDProgressiveImageCoder, SDAnimatedImageCoder>

/**
 * Returns the shared instance of the APNG coder.
 * This singleton instance can be used across the app for APNG encoding/decoding.
 */
@property (nonatomic, class, readonly, nonnull) SDImageAPNGCoder *sharedCoder;

@end