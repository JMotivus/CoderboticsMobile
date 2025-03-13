/*
* This file is part of the SDWebImage package.
* (c) Olivier Poitrey <rs@dailymotion.com>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Cross-platform display link wrapper.
 * - Uses `CADisplayLink` on iOS/tvOS
 * - Uses `CVDisplayLink` on macOS
 * - Uses `NSTimer` on watchOS
 *
 * Note: This class does not retain the target to avoid retain cycles.
 */
@interface SDDisplayLink : NSObject

/**
 * The target object that will receive display link callbacks.
 * This is a weak reference to avoid retain cycles.
 */
@property (readonly, nonatomic, weak, nullable) id target;

/**
 * The selector to be called on the target when the display link fires.
 */
@property (readonly, nonatomic, assign) SEL selector;

/**
 * The elapsed time in seconds since the previous callback.
 * If this is the first callback, returns the time between `start` and the callback.
 * Returns zero when the display link is not running.
 */
@property (readonly, nonatomic) NSTimeInterval duration;

/**
 * Indicates whether the display link is currently running.
 */
@property (readonly, nonatomic, getter=isRunning) BOOL running;

/**
 * Creates a new display link instance with the specified target and selector.
 *
 * @param target The object that will receive display link callbacks
 * @param sel The selector to be called on the target when the display link fires
 * @return A new display link instance
 */
+ (instancetype)displayLinkWithTarget:(id)target selector:(SEL)sel;

/**
 * Adds the display link to the specified run loop and mode.
 *
 * @param runloop The run loop to add the display link to
 * @param mode The run loop mode to add the display link to
 */
- (void)addToRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

/**
 * Removes the display link from the specified run loop and mode.
 *
 * @param runloop The run loop to remove the display link from
 * @param mode The run loop mode to remove the display link from
 */
- (void)removeFromRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

/**
 * Starts the display link.
 */
- (void)start;

/**
 * Stops the display link.
 */
- (void)stop;

@end

NS_ASSUME_NONNULL_END