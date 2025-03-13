/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"
#import "SDWebImageDefine.h"
#import "SDWebImageOperation.h"
#import "SDImageCoder.h"

#pragma mark - Callback Typedefs

/**
 * Callback for reporting progress during image loading
 * @param receivedSize Current size of data received
 * @param expectedSize Expected total size of the image data
 * @param targetURL The URL being loaded
 */
typedef void(^SDImageLoaderProgressBlock)(NSInteger receivedSize, NSInteger expectedSize, NSURL * _Nullable targetURL);

/**
 * Callback for image loading completion
 * @param image The loaded image, if successful
 * @param data The raw image data
 * @param error Error that occurred during loading, if any
 * @param finished Whether the loading process is complete
 */
typedef void(^SDImageLoaderCompletedBlock)(UIImage * _Nullable image, NSData * _Nullable data, NSError * _Nullable error, BOOL finished);

#pragma mark - Context Options

/**
 * A `UIImage` instance from `SDWebImageManager` when you specify `SDWebImageRefreshCached` and image cache hit.
 * This can be a hint for image loader to load the image from network and refresh the image from remote location if needed.
 * If the image from remote location does not change, you should call the completion with `SDWebImageErrorCacheNotModified` error.
 * @note If you don't implement `SDWebImageRefreshCached` support, you do not need to care about this context option.
 */
FOUNDATION_EXPORT SDWebImageContextOption _Nonnull const SDWebImageContextLoaderCachedImage;

#pragma mark - Helper methods

/**
 * Built-in decoding process for image downloaded from network or local file.
 * @note Use this to maintain compatibility with SDWebImage's behavior in custom loaders.
 *
 * @param imageData The image data from the network (required)
 * @param imageURL The image URL from the input (required)
 * @param options The options from the input
 * @param context The context from the input
 * @return The decoded image for the downloaded data
 */
FOUNDATION_EXPORT UIImage * _Nullable SDImageLoaderDecodeImageData(NSData * _Nonnull imageData, NSURL * _Nonnull imageURL, SDWebImageOptions options, SDWebImageContext * _Nullable context);

/**
 * Built-in decoding process for progressive image download from network.
 * Used when `SDWebImageProgressiveLoad` option is set.
 * @note Use this to maintain compatibility with SDWebImage's behavior in custom loaders.
 *
 * @param imageData The partial image data received so far (required)
 * @param imageURL The image URL from the input (required)
 * @param finished Whether all image data has been received
 * @param operation The loader operation associated with current download
 * @param options The options from the input
 * @param context The context from the input
 * @return The progressively decoded image
 */
FOUNDATION_EXPORT UIImage * _Nullable SDImageLoaderDecodeProgressiveImageData(NSData * _Nonnull imageData, NSURL * _Nonnull imageURL, BOOL finished, id<SDWebImageOperation> _Nonnull operation, SDWebImageOptions options, SDWebImageContext * _Nullable context);

/**
 * Retrieves the progressive decoder for the current loading operation.
 * @param operation The loading operation
 * @return The progressive decoder associated with the operation, or nil if none exists
 */
FOUNDATION_EXPORT id<SDProgressiveImageCoder> _Nullable SDImageLoaderGetProgressiveCoder(id<SDWebImageOperation> _Nonnull operation);

/**
 * Sets the progressive decoder for the current loading operation.
 * @param operation The loading operation to associate with the decoder
 * @param progressiveCoder The progressive decoder to associate, or nil to remove
 */
FOUNDATION_EXPORT void SDImageLoaderSetProgressiveCoder(id<SDWebImageOperation> _Nonnull operation, id<SDProgressiveImageCoder> _Nullable progressiveCoder);

#pragma mark - SDImageLoader Protocol

/**
 * Protocol to specify custom image loading processes.
 * 
 * Implementation guidelines:
 * 1. For network/file loading: Focus on data download, then use SDImageLoaderDecodeImageData
 *    or SDImageLoaderDecodeProgressiveImageData for decoding (in a global queue).
 * 2. For direct image instances (e.g., from Photos framework): Process data and image yourself.
 * 3. Always load images in a background queue to avoid blocking the main thread.
 *
 * @note SDWebImageManager typically calls these methods from the main queue.
 */
@protocol SDImageLoader <NSObject>

@required
/**
 * Legacy method to check if loader can handle the provided URL.
 * @deprecated Use canRequestImageForURL:options:context: instead
 *
 * @param url The image URL to check
 * @return YES to proceed with download, NO to abort
 */
- (BOOL)canRequestImageForURL:(nullable NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("canRequestImageForURL:options:context:", macos(10.10, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));

@optional
/**
 * Checks if loader can handle the provided URL with options and context.
 *
 * @param url The image URL to check
 * @param options Options for the request
 * @param context Context containing additional parameters
 * @return YES to proceed with download, NO to abort
 */
- (BOOL)canRequestImageForURL:(nullable NSURL *)url
                      options:(SDWebImageOptions)options
                      context:(nullable SDWebImageContext *)context;

@required
/**
 * Performs the image loading operation.
 *
 * @param url The URL representing the image (may not be HTTP)
 * @param options Options for the request
 * @param context Context containing additional parameters
 * @param progressBlock Called during download progress (on background queue)
 * @param completedBlock Called when operation completes
 * @return An operation object that allows cancellation
 */
- (nullable id<SDWebImageOperation>)requestImageWithURL:(nullable NSURL *)url
                                                options:(SDWebImageOptions)options
                                                context:(nullable SDWebImageContext *)context
                                               progress:(nullable SDImageLoaderProgressBlock)progressBlock
                                              completed:(nullable SDImageLoaderCompletedBlock)completedBlock;

/**
 * Legacy method to determine if a failed URL should be blacklisted.
 * @deprecated Use shouldBlockFailedURLWithURL:error:options:context: instead
 *
 * @param url The URL that failed to load
 * @param error The error from the failed load
 * @return YES to blacklist this URL, NO to allow retrying
 */
- (BOOL)shouldBlockFailedURLWithURL:(nonnull NSURL *)url
                              error:(nonnull NSError *)error API_DEPRECATED_WITH_REPLACEMENT("shouldBlockFailedURLWithURL:error:options:context:", macos(10.10, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));

@optional
/**
 * Determines if a failed URL should be blacklisted, with options and context.
 *
 * @param url The URL that failed to load
 * @param error The error from the failed load
 * @param options Options used for the request
 * @param context Context used for the request
 * @return YES to blacklist this URL, NO to allow retrying
 */
- (BOOL)shouldBlockFailedURLWithURL:(nonnull NSURL *)url
                              error:(nonnull NSError *)error
                            options:(SDWebImageOptions)options
                            context:(nullable SDWebImageContext *)context;

@end