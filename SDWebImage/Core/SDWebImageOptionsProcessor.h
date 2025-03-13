/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"
#import "SDWebImageDefine.h"

@class SDWebImageOptionsResult;

/**
 * Block definition for options processor.
 * @param url The URL to the image
 * @param options A mask to specify options to use for this request
 * @param context A context containing additional options
 * @return The processed options result
 */
typedef SDWebImageOptionsResult * _Nullable(^SDWebImageOptionsProcessorBlock)(NSURL * _Nullable url, SDWebImageOptions options, SDWebImageContext * _Nullable context);

/**
 * The options result contains both options and context.
 * This class encapsulates the parameters used for image loading operations.
 */
@interface SDWebImageOptionsResult : NSObject

/**
 * WebCache options.
 */
@property (nonatomic, assign, readonly) SDWebImageOptions options;

/**
 * Context options.
 */
@property (nonatomic, copy, readonly, nullable) SDWebImageContext *context;

/**
 * Create a new options result.
 *
 * @param options WebCache options
 * @param context Context options
 * @return The options result containing both options and context
 */
- (nonnull instancetype)initWithOptions:(SDWebImageOptions)options 
                                context:(nullable SDWebImageContext *)context;

- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;

@end

/**
 * Protocol for options processor.
 * Options processor can be used to control the final result for individual image request's
 * `SDWebImageOptions` and `SDWebImageContext`. Implement this protocol to have global control
 * for each individual image request's options.
 */
@protocol SDWebImageOptionsProcessor <NSObject>

/**
 * Return the processed options result for a specific image URL, with its options and context
 *
 * @param url The URL to the image
 * @param options A mask to specify options to use for this request
 * @param context A context containing different options to perform specific changes or processes
 * @return The processed result, containing both options and context
 */
- (nullable SDWebImageOptionsResult *)processedResultForURL:(nullable NSURL *)url
                                                    options:(SDWebImageOptions)options
                                                    context:(nullable SDWebImageContext *)context;

@end

/**
 * A concrete options processor implementation that uses a block.
 * This allows for easy creation of options processors using blocks.
 */
@interface SDWebImageOptionsProcessor : NSObject<SDWebImageOptionsProcessor>

/**
 * Create an options processor with the provided block.
 *
 * @param block The block to be called for processing options
 * @return A new options processor instance
 */
+ (nonnull instancetype)optionsProcessorWithBlock:(nonnull SDWebImageOptionsProcessorBlock)block;

/**
 * Initialize an options processor with the provided block.
 *
 * @param block The block to be called for processing options
 * @return A new options processor instance
 */
- (nonnull instancetype)initWithBlock:(nonnull SDWebImageOptionsProcessorBlock)block;

- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;

@end