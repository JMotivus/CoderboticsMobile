/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"
#import "NSData+ImageContentType.h"
#import "SDImageCoder.h"

/**
 * UIImage category for image metadata, including animation, loop count, format, incremental, etc.
 * This category provides properties to access and modify image metadata across different platforms.
 */
@interface UIImage (Metadata)

#pragma mark - Animation Properties

/**
 * The number of times to repeat an animated image.
 *
 * UIKit:
 * - For static image format, this value is always 0.
 * - For animated image format, 0 means infinite looping.
 * - Note: This property can get out of sync if you create another instance with CGImage or other methods.
 *
 * AppKit:
 * - NSImage supports animation via `NSBitmapImageRep`(GIF) or `SDAnimatedImageRep`(APNG/GIF/WebP).
 * - The getter retrieves the loop count from animated imageRep.
 * - The setter updates the loop count in animated imageRep.
 *
 * SDAnimatedImage:
 * - Returns `animatedImageLoopCount`
 */
@property (nonatomic, assign) NSUInteger sd_imageLoopCount;

/**
 * The number of frames in the image.
 *
 * UIKit:
 * - Returns the `images`'s count adjusted for different frame durations.
 * - Matches the real visible frame count when displaying on UIImageView.
 * - Returns 1 for static image.
 *
 * AppKit:
 * - Returns the underlying `NSBitmapImageRep` or `SDAnimatedImageRep` frame count.
 * - Returns 1 for static image.
 *
 * SDAnimatedImage:
 * - Returns `animatedImageFrameCount` for animated image, 1 for static image.
 */
@property (nonatomic, assign, readonly) NSUInteger sd_imageFrameCount;

/**
 * Whether the image is animated.
 *
 * UIKit:
 * - Checks the `images` array property.
 *
 * AppKit:
 * - NSImage supports animation via GIF imageRep.
 * - Checks if the imageRep's frame count > 1.
 *
 * SDAnimatedImage:
 * - Checks if `animatedImageFrameCount` > 1
 */
@property (nonatomic, assign, readonly) BOOL sd_isAnimated;

#pragma mark - Image Format Properties

/**
 * Whether the image is a vector format.
 *
 * UIKit:
 * - Checks the `isSymbolImage` property.
 * - Also checks system PDF(iOS 11+) && SVG(iOS 13+) support.
 *
 * AppKit:
 * - NSImage supports PDF, SVG, and EPS imageRep.
 * - Checks the imageRep class.
 *
 * SDAnimatedImage:
 * - Always returns `NO`
 */
@property (nonatomic, assign, readonly) BOOL sd_isVector;

/**
 * The image format representing the original compressed image data format.
 *
 * If not manually specified, this information is retrieved from CGImage using `CGImageGetUTType`.
 * May return nil for non-CG based images, defaulting to `SDImageFormatUndefined`.
 *
 * @note This property can get out of sync if you create another instance with CGImage or other methods.
 * @note For `SDAnimatedImage`, returns `animatedImageFormat` when animated, or fallback when static.
 */
@property (nonatomic, assign) SDImageFormat sd_imageFormat;

/**
 * Whether the image is using HDR (High Dynamic Range).
 *
 * @note Only valid for CGImage-based images. For CIImage-based images, the returned value may not be correct.
 */
@property (nonatomic, assign, readonly) BOOL sd_isHighDynamicRange;

#pragma mark - Decoding Properties

/**
 * Whether the image is during incremental decoding and may not contain full pixels.
 */
@property (nonatomic, assign) BOOL sd_isIncremental;

/**
 * Whether the image has been transformed from the original image.
 * 
 * When true, the image data may not match the original downloaded data.
 */
@property (nonatomic, assign) BOOL sd_isTransformed;

/**
 * Whether the image is using thumbnail decode with smaller size.
 *
 * @note This checks if `sd_decodeOptions[.decodeThumbnailPixelSize] > CGSize.zero`
 * When true, the image data may not match the original downloaded data.
 */
@property (nonatomic, assign, readonly) BOOL sd_isThumbnail;

/**
 * The decode options used when decoded from SDWebImage loading system.
 *
 * Contains image decoding related options including:
 * - .decodeScaleFactor
 * - .decodeThumbnailPixelSize
 * - .decodePreserveAspectRatio
 * - .decodeFirstFrameOnly
 *
 * @note Used to identify thumbnail decoding. When from thumbnail decoding, the callback's data will be nil.
 * @warning Do not store objects that keep strong references to the image itself to avoid retain cycles.
 * @warning This API exists due to current SDWebImageDownloader design limitations and may be refactored in future.
 */
@property (nonatomic, copy) SDImageCoderOptions *sd_decodeOptions;

@end