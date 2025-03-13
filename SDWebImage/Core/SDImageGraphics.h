/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"
#import <CoreGraphics/CoreGraphics.h>

/**
 * These graphics context methods provide a cross-platform (AppKit/UIKit) interface for drawing operations.
 *
 * - For UIKit: These methods directly map to equivalent methods in `UIGraphics.h`.
 * - For AppKit: These methods use `NSGraphicsContext` to create image contexts that match UIKit behavior.
 *
 * @note For better memory performance when working with ARGB8888 bitmap format, consider using
 * `SDGraphicsImageRenderer` instead, which is more efficient for RAM usage.
 */

/**
 * Returns the current graphics context.
 *
 * @return The current Core Graphics context, or NULL if no context is current.
 */
FOUNDATION_EXPORT CGContextRef __nullable SDGraphicsGetCurrentContext(void) CF_RETURNS_NOT_RETAINED;

/**
 * Creates a bitmap-based graphics context and makes it the current context.
 * This is a convenience method that calls SDGraphicsBeginImageContextWithOptions with default values.
 *
 * @param size The size of the bitmap context in points.
 */
FOUNDATION_EXPORT void SDGraphicsBeginImageContext(CGSize size);

/**
 * Creates a bitmap-based graphics context with the specified options and makes it the current context.
 *
 * @param size The size of the bitmap context in points.
 * @param opaque A Boolean value indicating whether the bitmap is opaque.
 * @param scale The scale factor to apply to the bitmap. Use 0.0 to use the device's main screen scale.
 */
FOUNDATION_EXPORT void SDGraphicsBeginImageContextWithOptions(CGSize size, BOOL opaque, CGFloat scale);

/**
 * Removes the current bitmap-based graphics context from the top of the stack.
 * Call this method to balance a previous call to SDGraphicsBeginImageContext or SDGraphicsBeginImageContextWithOptions.
 */
FOUNDATION_EXPORT void SDGraphicsEndImageContext(void);

/**
 * Returns an image based on the contents of the current bitmap-based graphics context.
 *
 * @return A new UIImage object or nil if no current bitmap-based context exists.
 */
FOUNDATION_EXPORT UIImage * __nullable SDGraphicsGetImageFromCurrentImageContext(void);