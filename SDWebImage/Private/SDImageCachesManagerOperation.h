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
 * SDImageCachesManagerOperation
 * 
 * A specialized operation class used for managing cache operations.
 * This class is used for tracking the progress of multiple cache operations
 * but is not intended to be used for operation queue execution.
 */
@interface SDImageCachesManagerOperation : NSOperation

/**
 * The number of pending operations that have not yet completed.
 * This is a readonly property that indicates how many operations are still in progress.
 */
@property (nonatomic, assign, readonly) NSUInteger pendingCount;

/**
 * Initializes the operation with the total count of expected operations.
 * This should be called before starting to track individual operations.
 *
 * @param totalCount The total number of operations to be tracked
 */
- (void)beginWithTotalCount:(NSUInteger)totalCount;

/**
 * Marks one operation as complete and decrements the pending count.
 * Call this method when an individual operation finishes.
 */
- (void)completeOne;

/**
 * Marks the entire operation as finished.
 * Call this method when all operations are complete or when you want to
 * forcibly finish the operation regardless of pending count.
 */
- (void)done;

@end