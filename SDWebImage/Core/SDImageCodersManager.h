/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDImageCoder.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * SDImageCodersManager
 *
 * A singleton manager that maintains a priority queue of image coders.
 * The manager itself conforms to SDImageCoder protocol, acting as a composite coder
 * that delegates operations to the appropriate coder in its queue.
 *
 * Priority is determined by the order in the queue - the last added coder has the highest priority.
 * When encoding/decoding, each coder is asked in order if it can handle the data until one returns YES.
 *
 * Usage:
 * - Default coders: `IOCoder`, `GIFCoder`, `APNGCoder` (internally set)
 * - After adding a custom coder: `[SDImageCodersManager.sharedManager addCoder:[MyCrazyCoder new]]`
 * - The `coders` property returns the coders in their priority order
 *
 * Requirements:
 * - Coders must conform to `SDImageCoder` protocol
 * - Progressive coders should conform to `SDProgressiveImageCoder` protocol
 */
@interface SDImageCodersManager : NSObject <SDImageCoder>

/**
 * Returns the global shared coders manager instance.
 */
@property (nonatomic, class, readonly, nonnull) SDImageCodersManager *sharedManager;

/**
 * All coders in the manager.
 * The array is a priority queue - the later added coder will have the highest priority.
 */
@property (nonatomic, copy, nullable) NSArray<id<SDImageCoder>> *coders;

/**
 * Adds a new coder to the end of coders array, giving it the highest priority.
 *
 * @param coder The coder to add
 */
- (void)addCoder:(nonnull id<SDImageCoder>)coder;

/**
 * Removes a coder from the coders array.
 *
 * @param coder The coder to remove
 */
- (void)removeCoder:(nonnull id<SDImageCoder>)coder;

@end

NS_ASSUME_NONNULL_END