/*
* This file is part of the SDWebImage package.
* (c) Olivier Poitrey <rs@dailymotion.com>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#import <Foundation/Foundation.h>
#import <ImageIO/ImageIO.h>
#import "SDImageIOAnimatedCoder.h"

#pragma mark - Version Compatibility Definitions

// Xcode 16 SDK contains HDR encoding API, but we still support Xcode 15
#define SD_IMAGEIO_HDR_ENCODING (__IPHONE_OS_VERSION_MAX_ALLOWED >= 180000)

#pragma mark - UTI Type Definitions

/**
 * Image format UTI types enumeration
 * Used to identify different image formats
 */
typedef NS_ENUM(NSInteger, SDImageUTIType) {
    // Base image type
    SDUTTypeImage = 0,
    
    // Common image formats
    SDUTTypeJPEG,
    SDUTTypePNG,
    SDUTTypeTIFF,
    SDUTTypeSVG,
    SDUTTypeGIF,
    SDUTTypePDF,
    SDUTTypeBMP,
    SDUTTypeRAW,
    
    // HEIC/HEIF formats
    SDUTTypeHEIC,
    SDUTTypeHEIF,
    SDUTTypeHEICS,
    
    // WebP format
    SDUTTypeWebP
};

#pragma mark - UTI String Constants

// Standard image UTI types
#define kSDUTTypeImage ((__bridge CFStringRef)@"public.image")
#define kSDUTTypeJPEG  ((__bridge CFStringRef)@"public.jpeg")
#define kSDUTTypePNG   ((__bridge CFStringRef)@"public.png")
#define kSDUTTypeTIFF  ((__bridge CFStringRef)@"public.tiff")
#define kSDUTTypeSVG   ((__bridge CFStringRef)@"public.svg-image")
#define kSDUTTypeGIF   ((__bridge CFStringRef)@"com.compuserve.gif")
#define kSDUTTypePDF   ((__bridge CFStringRef)@"com.adobe.pdf")
#define kSDUTTypeBMP   ((__bridge CFStringRef)@"com.microsoft.bmp")
#define kSDUTTypeRAW   ((__bridge CFStringRef)@"public.camera-raw-image")

// HEIC/HEIF formats - AVFileTypeHEIC/AVFileTypeHEIF is defined in AVFoundation via iOS 11
#define kSDUTTypeHEIC  ((__bridge CFStringRef)@"public.heic")
#define kSDUTTypeHEIF  ((__bridge CFStringRef)@"public.heif")
#define kSDUTTypeHEICS ((__bridge CFStringRef)@"public.heics") // HEIC Sequence (Animated Image)

// WebP format - not defined in public UTI framework, Apple uses hardcoded string
#define kSDUTTypeWebP  ((__bridge CFStringRef)@"org.webmproject.webp")

/**
 * SDImageIOAnimatedCoder private interface
 * Provides utility methods for handling animated images with ImageIO
 */
@interface SDImageIOAnimatedCoder ()

/**
 * Get the frame duration from an image source at specified index
 *
 * @param index The frame index
 * @param source The CGImageSource
 * @return The frame duration in seconds
 */
+ (NSTimeInterval)frameDurationAtIndex:(NSUInteger)index source:(nonnull CGImageSourceRef)source;

/**
 * Get the loop count from an image source
 *
 * @param source The CGImageSource
 * @return The loop count, 0 means infinite
 */
+ (NSUInteger)imageLoopCountWithSource:(nonnull CGImageSourceRef)source;

/**
 * Create a frame from an image source at specified index
 *
 * @param index The frame index
 * @param source The CGImageSource
 * @param scale The image scale factor
 * @param preserveAspectRatio Whether to preserve aspect ratio
 * @param thumbnailSize The thumbnail size
 * @param lazyDecode Whether to use lazy decoding
 * @param animatedImage Whether the image is animated
 * @param decodeToHDR Whether to decode to HDR
 * @return The created frame as UIImage
 */
+ (nullable UIImage *)createFrameAtIndex:(NSUInteger)index 
                                  source:(nonnull CGImageSourceRef)source 
                                   scale:(CGFloat)scale 
                     preserveAspectRatio:(BOOL)preserveAspectRatio 
                           thumbnailSize:(CGSize)thumbnailSize 
                              lazyDecode:(BOOL)lazyDecode 
                           animatedImage:(BOOL)animatedImage 
                             decodeToHDR:(BOOL)decodeToHDR;

/**
 * Check if the coder can encode to the specified format
 *
 * @param format The image format to check
 * @return YES if can encode, NO otherwise
 */
+ (BOOL)canEncodeToFormat:(SDImageFormat)format;

/**
 * Check if the coder can decode from the specified format
 *
 * @param format The image format to check
 * @return YES if can decode, NO otherwise
 */
+ (BOOL)canDecodeFromFormat:(SDImageFormat)format;

@end