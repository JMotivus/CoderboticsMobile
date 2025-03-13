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
 * Block type for request modification operations.
 * Takes an NSURLRequest and returns a modified NSURLRequest or nil to cancel the request.
 */
typedef NSURLRequest * _Nullable (^SDWebImageDownloaderRequestModifierBlock)(NSURLRequest * _Nonnull request);

/**
 * Protocol for downloader request modifier.
 * Using a protocol makes this extensible and allows Swift users to implement it
 * without needing to use `@convention(block)` to store blocks in context options.
 */
@protocol SDWebImageDownloaderRequestModifier <NSObject>

/**
 * Modify the original URL request and return a new one.
 * @param request The original URL request for image loading
 * @return A modified request or nil to cancel the request
 */
- (nullable NSURLRequest *)modifiedRequestWithRequest:(nonnull NSURLRequest *)request;

@end

/**
 * A downloader request modifier implementation that uses a block for modification logic.
 */
@interface SDWebImageDownloaderRequestModifier : NSObject <SDWebImageDownloaderRequestModifier>

/**
 * Create the request modifier with a block
 * @param block A block to control modifier logic
 * @return A new instance of SDWebImageDownloaderRequestModifier
 */
- (nonnull instancetype)initWithBlock:(nonnull SDWebImageDownloaderRequestModifierBlock)block;

/**
 * Create the request modifier with a block (class factory method)
 * @param block A block to control modifier logic
 * @return A new instance of SDWebImageDownloaderRequestModifier
 */
+ (nonnull instancetype)requestModifierWithBlock:(nonnull SDWebImageDownloaderRequestModifierBlock)block;

- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;

@end

/**
 * Convenience methods for creating request modifiers with common HTTP configurations.
 */
@interface SDWebImageDownloaderRequestModifier (Conveniences)

/**
 * Create a request modifier with HTTP Method.
 * @param method HTTP Method, nil means to GET.
 * @return A new instance of SDWebImageDownloaderRequestModifier
 */
- (nonnull instancetype)initWithMethod:(nullable NSString *)method;

/**
 * Create a request modifier with HTTP Headers.
 * @param headers HTTP Headers. Case insensitive according to HTTP/1.1(HTTP/2) standard.
 *                The headers will override the same fields from original request.
 * @return A new instance of SDWebImageDownloaderRequestModifier
 */
- (nonnull instancetype)initWithHeaders:(nullable NSDictionary<NSString *, NSString *> *)headers;

/**
 * Create a request modifier with HTTP Body.
 * @param body HTTP Body.
 * @return A new instance of SDWebImageDownloaderRequestModifier
 */
- (nonnull instancetype)initWithBody:(nullable NSData *)body;

/**
 * Create a request modifier with HTTP Method, Headers and Body.
 * @param method HTTP Method, nil means to GET.
 * @param headers HTTP Headers. Case insensitive according to HTTP/1.1(HTTP/2) standard.
 *                The headers will override the same fields from original request.
 * @param body HTTP Body.
 * @return A new instance of SDWebImageDownloaderRequestModifier
 */
- (nonnull instancetype)initWithMethod:(nullable NSString *)method 
                               headers:(nullable NSDictionary<NSString *, NSString *> *)headers 
                                  body:(nullable NSData *)body;

@end