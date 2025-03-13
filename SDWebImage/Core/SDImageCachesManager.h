/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <Foundation/Foundation.h>
#import "SDImageCacheDefine.h"

/**
 * Policy for cache operations in SDImageCachesManager.
 * Defines how operations are executed across multiple caches.
 */
typedef NS_ENUM(NSUInteger, SDImageCachesManagerOperationPolicy) {
    /**
     * Process all caches serially from highest to lowest priority.
     * Operations stop when a successful result is found.
     */
    SDImageCachesManagerOperationPolicySerial,
    
    /**
     * Process all caches concurrently.
     * All caches will be operated on regardless of individual results.
     */
    SDImageCachesManagerOperationPolicyConcurrent,
    
    /**
     * Process only the highest priority cache (last added).
     * Ignores all other caches in the manager.
     */
    SDImageCachesManagerOperationPolicyHighestOnly,
    
    /**
     * Process only the lowest priority cache (first added).
     * Ignores all other caches in the manager.
     */
    SDImageCachesManagerOperationPolicyLowestOnly
};

/**
 * A manager that coordinates operations across multiple cache instances.
 * Allows for different operation policies for different cache operations.
 */
@interface SDImageCachesManager : NSObject <SDImageCache>

/**
 * Returns the global shared caches manager instance.
 * By default, this includes the `SDImageCache.sharedImageCache` in the caches array.
 *
 * @return The shared manager instance
 */
@property (nonatomic, class, readonly, nonnull) SDImageCachesManager *sharedManager;

#pragma mark - Operation Policies

/**
 * Operation policy for query operations.
 * Defaults to `Serial`, which queries caches serially until one returns a non-nil image.
 */
@property (nonatomic, assign) SDImageCachesManagerOperationPolicy queryOperationPolicy;

/**
 * Operation policy for store operations.
 * Defaults to `HighestOnly`, which stores only in the highest priority cache.
 */
@property (nonatomic, assign) SDImageCachesManagerOperationPolicy storeOperationPolicy;

/**
 * Operation policy for remove operations.
 * Defaults to `Concurrent`, which removes from all caches concurrently.
 */
@property (nonatomic, assign) SDImageCachesManagerOperationPolicy removeOperationPolicy;

/**
 * Operation policy for contains operations.
 * Defaults to `Serial`, which checks caches serially until one returns a non-None containsCacheType.
 */
@property (nonatomic, assign) SDImageCachesManagerOperationPolicy containsOperationPolicy;

/**
 * Operation policy for clear operations.
 * Defaults to `Concurrent`, which clears all caches concurrently.
 */
@property (nonatomic, assign) SDImageCachesManagerOperationPolicy clearOperationPolicy;

/**
 * All caches managed by this manager.
 * The caches array acts as a priority queue - the later added cache has higher priority.
 */
@property (nonatomic, copy, nullable) NSArray<id<SDImageCache>> *caches;

#pragma mark - Cache Management

/**
 * Adds a new cache to the end of the caches array, giving it the highest priority.
 *
 * @param cache The cache to add
 */
- (void)addCache:(nonnull id<SDImageCache>)cache;

/**
 * Removes a specific cache from the caches array.
 *
 * @param cache The cache to remove
 */
- (void)removeCache:(nonnull id<SDImageCache>)cache;

@end