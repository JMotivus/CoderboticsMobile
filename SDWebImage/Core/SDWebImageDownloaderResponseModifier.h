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
 * Block type for response modification operations.
 * Takes an original response and returns a modified response.
 */
typedef NSURLResponse * _Nullable (^SDWebImageDownloaderResponseModifierBlock)(NSURLResponse * _Nonnull response);

/**
 * Protocol for downloader response modifier.
 * Using a protocol makes this extensible and allows Swift users to implement it
 * without needing to use `@convention(block)` to store blocks in context options.
 */
@protocol SDWebImageDownloaderResponseModifier <NSObject>

/**
 * Modify the original URL response and return a new response.
 * Can be used to check MIME-Type, mock server responses, etc.
 *
 * @param response The original URL response (for HTTP requests, this is an NSHTTPURLResponse)
 * @return A modified response or nil (nil will cancel the download with SDWebImageErrorInvalidDownloadResponse)
 */
- (nullable NSURLResponse *)modifiedResponseWithResponse:(nonnull NSURLResponse *)response;

@end

/**
 * A downloader response modifier implementation that uses a block for modification logic.
 */
@interface SDWebImageDownloaderResponseModifier : NSObject <SDWebImageDownloaderResponseModifier>

/**
 * Create a response modifier with the specified block.
 *
 * @param block Block that defines the modification logic
 * @return A new response modifier instance
 */
- (nonnull instancetype)initWithBlock:(nonnull SDWebImageDownloaderResponseModifierBlock)block;

/**
 * Class factory method to create a response modifier with the specified block.
 *
 * @param block Block that defines the modification logic
 * @return A new response modifier instance
 */
+ (nonnull instancetype)responseModifierWithBlock:(nonnull SDWebImageDownloaderResponseModifierBlock)block;

- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;

@end

/**
 * Convenience methods for creating response modifiers with common HTTP modifications.
 */
@interface SDWebImageDownloaderResponseModifier (Conveniences)

/**
 * Create a response modifier that sets a specific HTTP status code.
 *
 * @param statusCode The HTTP status code to use
 * @return A new response modifier instance
 */
- (nonnull instancetype)initWithStatusCode:(NSInteger)statusCode;

/**
 * Create a response modifier that sets a specific HTTP version.
 * Status code defaults to 200.
 *
 * @param version HTTP version string (defaults to "HTTP/1.1" if nil)
 * @return A new response modifier instance
 */
- (nonnull instancetype)initWithVersion:(nullable NSString *)version;

/**
 * Create a response modifier that sets specific HTTP headers.
 * Status code defaults to 200.
 *
 * @param headers HTTP headers dictionary (case insensitive per HTTP standards)
 *                These headers will override matching fields from the original response
 * @return A new response modifier instance
 */
- (nonnull instancetype)initWithHeaders:(nullable NSDictionary<NSString *, NSString *> *)headers;

/**
 * Create a response modifier that sets HTTP status code, version and headers.
 *
 * @param statusCode HTTP status code
 * @param version HTTP version string (defaults to "HTTP/1.1" if nil)
 * @param headers HTTP headers dictionary (case insensitive per HTTP standards)
 *                These headers will override matching fields from the original response
 * @return A new response modifier instance
 */
- (nonnull instancetype)initWithStatusCode:(NSInteger)statusCode 
                                   version:(nullable NSString *)version 
                                   headers:(nullable NSDictionary<NSString *, NSString *> *)headers;

@end