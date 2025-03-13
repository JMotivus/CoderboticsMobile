/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"

/**
 * Operation execution order for download operations
 */
typedef NS_ENUM(NSInteger, SDWebImageDownloaderExecutionOrder) {
    /**
     * Default value. All download operations will execute in queue style (first-in-first-out).
     */
    SDWebImageDownloaderFIFOExecutionOrder,
    
    /**
     * All download operations will execute in stack style (last-in-first-out).
     */
    SDWebImageDownloaderLIFOExecutionOrder
};

/**
 * Configuration class for image downloader settings
 * @note This class conforms to NSCopying, make sure to add any new properties in `copyWithZone:` as well.
 */
@interface SDWebImageDownloaderConfig : NSObject <NSCopying>

/**
 * Gets the default downloader config used for shared instance or initialization when no config is provided.
 * Used by instances like `SDWebImageDownloader.sharedDownloader`.
 * @note You can modify properties on the default config to affect future downloader instances.
 * Existing downloader instances will not be affected by these changes.
 */
@property (nonatomic, class, readonly, nonnull) SDWebImageDownloaderConfig *defaultDownloaderConfig;

#pragma mark - Network Configuration

/**
 * The maximum number of concurrent downloads.
 * Defaults to 6.
 */
@property (nonatomic, assign) NSInteger maxConcurrentDownloads;

/**
 * The timeout value (in seconds) for each download operation.
 * Defaults to 15.0.
 */
@property (nonatomic, assign) NSTimeInterval downloadTimeout;

/**
 * The custom session configuration used by NSURLSession.
 * If not provided, `defaultSessionConfiguration` will be used.
 * Defaults to nil.
 * @note This property is immutable after the downloader instance is initialized.
 */
@property (nonatomic, strong, nullable) NSURLSessionConfiguration *sessionConfiguration;

#pragma mark - Authentication

/**
 * The default URL credential for request operations.
 * Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSURLCredential *urlCredential;

/**
 * Username for HTTP Basic authentication.
 * Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *username;

/**
 * Password for HTTP Basic authentication.
 * Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *password;

#pragma mark - Operation Settings

/**
 * The minimum interval for progress updates during network downloading.
 * The next progress callback will only be triggered when the progress percent difference
 * is greater than or equal to this value. Final completion callbacks are not affected.
 * Value should be between 0.0 and 1.0.
 * @note This affects progressive image decoding refresh rate.
 * @note Higher values may improve performance by reducing callback frequency.
 * Defaults to 0, which means progress callbacks occur immediately on new data.
 */
@property (nonatomic, assign) double minimumProgressInterval;

/**
 * Subclass of `SDWebImageDownloaderOperation` to use as the default operation
 * for downloading images.
 * Defaults to nil (which uses `SDWebImageDownloaderOperation`).
 * @note Set this to a class conforming to `NSOperation<SDWebImageDownloaderOperation>`.
 */
@property (nonatomic, assign, nullable) Class operationClass;

/**
 * Download operations execution order.
 * Defaults to `SDWebImageDownloaderFIFOExecutionOrder`.
 */
@property (nonatomic, assign) SDWebImageDownloaderExecutionOrder executionOrder;

#pragma mark - Response Validation

/**
 * Acceptable HTTP response status codes.
 * Status codes outside this range will mark the download operation as failed
 * with error code `SDWebImageErrorInvalidDownloadStatusCode`.
 * Defaults to [200,400). Set to nil to disable status code validation.
 */
@property (nonatomic, copy, nullable) NSIndexSet *acceptableStatusCodes;

/**
 * Acceptable HTTP response content types.
 * Content types not in this set will mark the download operation as failed
 * with error code `SDWebImageErrorInvalidDownloadContentType`.
 * Defaults to nil (no validation). Usually not needed as image format detection
 * uses file signature magic bytes.
 */
@property (nonatomic, copy, nullable) NSSet<NSString *> *acceptableContentTypes;

@end