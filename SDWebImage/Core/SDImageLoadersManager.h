/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDImageLoader.h"

/**
 * A manager that coordinates multiple image loaders with priority handling.
 * Loaders are arranged in a priority queue where the most recently added loader
 * has the highest priority.
 */
@interface SDImageLoadersManager : NSObject <SDImageLoader>

/**
 * Returns the global shared loaders manager instance.
 * By default, this includes [`SDWebImageDownloader.sharedDownloader`] in the loaders array.
 *
 * @return The singleton instance of SDImageLoadersManager
 */
@property (nonatomic, class, readonly, nonnull) SDImageLoadersManager *sharedManager;

/**
 * The array of image loaders managed by this instance.
 * This array acts as a priority queue - the loader at the highest index has the highest priority.
 * When loading an image, loaders are tried in order from highest to lowest priority.
 */
@property (nonatomic, copy, nullable) NSArray<id<SDImageLoader>> *loaders;

/**
 * Adds a new image loader to the end of the loaders array, giving it the highest priority.
 *
 * @param loader The loader to add. Must not be nil.
 */
- (void)addLoader:(nonnull id<SDImageLoader>)loader;

/**
 * Removes an image loader from the loaders array.
 *
 * @param loader The loader to remove. Must not be nil.
 */
- (void)removeLoader:(nonnull id<SDImageLoader>)loader;

@end