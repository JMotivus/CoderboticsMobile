/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 * (c) Jamie Pinkham
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

/**
 * Error domain for SDWebImage loading system with custom error codes.
 * Used to identify errors specific to the SDWebImage framework.
 */
FOUNDATION_EXPORT NSErrorDomain const _Nonnull SDWebImageErrorDomain;

/**
 * Error user info keys for additional error context
 */
/// The response instance for invalid download response (NSURLResponse *)
FOUNDATION_EXPORT NSErrorUserInfoKey const _Nonnull SDWebImageErrorDownloadResponseKey;
/// The HTTP status code for invalid download response (NSNumber *)
FOUNDATION_EXPORT NSErrorUserInfoKey const _Nonnull SDWebImageErrorDownloadStatusCodeKey;
/// The HTTP MIME content type for invalid download response (NSString *)
FOUNDATION_EXPORT NSErrorUserInfoKey const _Nonnull SDWebImageErrorDownloadContentTypeKey;

/**
 * SDWebImage error codes enumeration
 * Organized by category (1xxx for client/input errors, 2xxx for network/operation errors)
 */
typedef NS_ERROR_ENUM(SDWebImageErrorDomain, SDWebImageError) {
    // Client/Input errors (1000-1999)
    /// The URL is invalid, such as nil URL or corrupted URL
    SDWebImageErrorInvalidURL = 1000,
    /// The image data can not be decoded to image, or the image data is empty
    SDWebImageErrorBadImageData = 1001,
    /// The remote location specify that the cached image is not modified, such as the HTTP response 304 code. It's useful for `SDWebImageRefreshCached`
    SDWebImageErrorCacheNotModified = 1002,
    /// The URL is blacklisted because of unrecoverable failure marked by downloader (such as 404), you can use `.retryFailed` option to avoid this
    SDWebImageErrorBlackListed = 1003,
    
    // Network/Operation errors (2000-2999)
    /// The image download operation is invalid, such as nil operation or unexpected error occur when operation initialized
    SDWebImageErrorInvalidDownloadOperation = 2000,
    /// The image download response a invalid status code. You can check the status code in error's userInfo under `SDWebImageErrorDownloadStatusCodeKey`
    SDWebImageErrorInvalidDownloadStatusCode = 2001,
    /// The image loading operation is cancelled before finished, during either async disk cache query, or waiting before actual network request. For actual network request error, check `NSURLErrorDomain` error domain and code.
    SDWebImageErrorCancelled = 2002,
    /// When using response modifier, the modified download response is nil and marked as failed.
    SDWebImageErrorInvalidDownloadResponse = 2003,
    /// The image download response a invalid content type. You can check the MIME content type in error's userInfo under `SDWebImageErrorDownloadContentTypeKey`
    SDWebImageErrorInvalidDownloadContentType = 2004
};