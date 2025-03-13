/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"
#import "SDWebImageOperation.h"

/**
 * UIView category for managing image loading operations.
 * 
 * These methods support canceling UIView image loading operations and are designed for internal use.
 * All stored operations use weak references and will be deallocated after image loading completes.
 * If you need to maintain strong references to operations, implement your own storage mechanism.
 */
@interface UIView (WebCacheOperation)

/**
 * Retrieves the image load operation for the specified key.
 *
 * @param key Key for identifying the operation. If nil, NSStringFromClass(self.class) will be used.
 * @return The image load operation associated with the key, or nil if none exists.
 */
- (nullable id<SDWebImageOperation>)sd_imageLoadOperationForKey:(nullable NSString *)key;

/**
 * Stores an image load operation in a UIView-based weak map table.
 *
 * @param operation The operation to store. If nil, no action will be performed.
 * @param key Key for storing the operation. If nil, NSStringFromClass(self.class) will be used.
 */
- (void)sd_setImageLoadOperation:(nullable id<SDWebImageOperation>)operation forKey:(nullable NSString *)key;

/**
 * Cancels and removes the image load operation for the current UIView and key.
 *
 * @param key Key for identifying the operation. If nil, NSStringFromClass(self.class) will be used.
 */
- (void)sd_cancelImageLoadOperationWithKey:(nullable NSString *)key;

/**
 * Removes the image load operation for the current UIView and key without cancelling it.
 *
 * @param key Key for identifying the operation. If nil, NSStringFromClass(self.class) will be used.
 */
- (void)sd_removeImageLoadOperationWithKey:(nullable NSString *)key;

@end