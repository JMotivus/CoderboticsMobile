/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

/**
 * UIImage category for memory cache cost.
 * This category adds memory cost calculation functionality to UIImage,
 * which is used by the image cache system to manage memory usage.
 */
@interface UIImage (MemoryCacheCost)

/**
 * The memory cache cost for the image used by image cache.
 * The cost function represents the bytes size held in memory.
 *
 * Behavior:
 * - For static images (`image.images` is nil): Returns the single frame bytes size
 * - For animated images (`image.images` is not nil): Returns the full frame bytes size
 * - For `NSImage`: Returns the single frame bytes size (NSImage doesn't store all frames in memory)
 *
 * @note If you set associated objects to `UIImage`, you can set a custom value to indicate the memory cost.
 * @note This property can get out of sync if you create another instance with CGImage or other methods due to category limitations.
 * @note Custom animated classes conforming to `SDAnimatedImage` can override this getter in their subclass to return a more accurate value.
 */
@property (assign, nonatomic) NSUInteger sd_memoryCost;

@end