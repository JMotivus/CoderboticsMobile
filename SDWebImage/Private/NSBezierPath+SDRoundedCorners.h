/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

#if SD_MAC

#import "UIImage+Transform.h"

/**
 * Category that extends NSBezierPath to provide rounded corner functionality
 * This mirrors the UIBezierPath API available on iOS for consistency across platforms
 */
@interface NSBezierPath (SDRoundedCorners)

/**
 * Creates a bezier path with the specified rounded corners.
 * 
 * @param rect The rectangle that defines the path's bounds
 * @param corners A bitmask value that identifies the corners to round
 * @param cornerRadius The radius of each rounded corner
 * @return A new bezier path object with the specified rounded corners
 */
+ (nonnull instancetype)sd_bezierPathWithRoundedRect:(NSRect)rect 
                                 byRoundingCorners:(SDRectCorner)corners 
                                      cornerRadius:(CGFloat)cornerRadius;

@end

#endif