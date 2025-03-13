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
 * SDWeakProxy
 * A weak proxy which forwards all messages to the target object.
 * This is useful to break retain cycles in delegates and timers.
 */
@interface SDWeakProxy : NSProxy

/**
 * The weak reference to the target object.
 * Messages sent to the proxy will be forwarded to this target.
 */
@property (nonatomic, weak, readonly, nullable) id target;

/**
 * Creates a new weak proxy with the specified target.
 *
 * @param target The object to which messages will be forwarded.
 * @return A new weak proxy instance.
 */
- (instancetype)initWithTarget:(id)target NS_DESIGNATED_INITIALIZER;

/**
 * Factory method to create a new weak proxy with the specified target.
 *
 * @param target The object to which messages will be forwarded.
 * @return A new weak proxy instance.
 */
+ (instancetype)proxyWithTarget:(id)target;

@end

NS_ASSUME_NONNULL_END