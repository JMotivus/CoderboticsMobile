/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

@class SDAsyncBlockOperation;

/**
 * Block type that defines the operation's asynchronous work.
 * The block receives the operation instance to allow calling complete when finished.
 */
typedef void (^SDAsyncBlock)(SDAsyncBlockOperation * __nonnull asyncOperation);

/**
 * An asynchronous operation that executes a block and completes only when explicitly told to.
 * Unlike NSBlockOperation which completes when the block returns, this operation
 * remains in-progress until the `complete` method is called.
 */
@interface SDAsyncBlockOperation : NSOperation

/**
 * Creates a new asynchronous block operation with the specified block.
 *
 * @param block The block to execute when the operation starts. This block must not be nil.
 * @return A newly initialized asynchronous block operation.
 */
- (nonnull instancetype)initWithBlock:(nonnull SDAsyncBlock)block;

/**
 * Convenience factory method to create a new asynchronous block operation.
 *
 * @param block The block to execute when the operation starts. This block must not be nil.
 * @return A newly initialized asynchronous block operation.
 */
+ (nonnull instancetype)blockOperationWithBlock:(nonnull SDAsyncBlock)block;

/**
 * Marks the operation as complete.
 * Call this method when the asynchronous work is finished to allow the operation queue to proceed.
 */
- (void)complete;

@end