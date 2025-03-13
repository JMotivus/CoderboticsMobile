/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>

/**
 * A protocol that represents a cancelable operation.
 * This protocol provides a common interface for operations that can be canceled.
 * It is used throughout SDWebImage to handle cancelable tasks like image loading.
 */
@protocol SDWebImageOperation <NSObject>

/**
 * Cancels the operation.
 * Implementations should ensure that resources are properly released when canceled.
 */
- (void)cancel;

@optional

/**
 * Indicates whether the operation has been cancelled.
 * @return YES if the operation was cancelled, NO otherwise.
 */
@property (nonatomic, assign, readonly, getter=isCancelled) BOOL cancelled;

@end

/**
 * NSOperation category that makes NSOperation conform to SDWebImageOperation protocol.
 * This allows NSOperation objects to be used wherever SDWebImageOperation is expected.
 */
@interface NSOperation (SDWebImageOperation) <SDWebImageOperation>

@end