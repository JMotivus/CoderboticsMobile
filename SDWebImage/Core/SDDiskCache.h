/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import "SDWebImageCompat.h"

@class SDImageCacheConfig;

/**
 A protocol to allow custom disk cache used in SDImageCache.
 
 All methods are called from the same global queue to avoid blocking on main queue
 and ensure thread-safety. However, implementers should also ensure thread-safety
 using locks or other synchronization mechanisms.
 */
@protocol SDDiskCache <NSObject>

@required
/**
 Create a new disk cache based on the specified path.
 
 @param cachePath Full path of a directory in which the cache will write data.
                 Once initialized you should not read and write to this directory.
 @param config The cache config to be used to create the cache.
 
 @return A new cache object, or nil if an error occurs.
 */
- (nullable instancetype)initWithCachePath:(nonnull NSString *)cachePath 
                                    config:(nonnull SDImageCacheConfig *)config;

/**
 Returns a boolean value that indicates whether a given key is in cache.
 This method may block the calling thread until file read is finished.
 
 @param key A string identifying the data. If nil, just return NO.
 @return Whether the key is in cache.
 */
- (BOOL)containsDataForKey:(nonnull NSString *)key;

/**
 Returns the data associated with a given key.
 This method may block the calling thread until file read is finished.
 
 @param key A string identifying the data. If nil, just return nil.
 @return The value associated with key, or nil if no value is associated with key.
 */
- (nullable NSData *)dataForKey:(nonnull NSString *)key;

/**
 Sets the value of the specified key in the cache.
 This method may block the calling thread until file write is finished.
 
 @param data The data to be stored in the cache.
 @param key  The key with which to associate the value. If nil, this method has no effect.
 */
- (void)setData:(nullable NSData *)data forKey:(nonnull NSString *)key;

/**
 Returns the extended data associated with a given key.
 This method may block the calling thread until file read is finished.
 
 @param key A string identifying the data. If nil, just return nil.
 @return The value associated with key, or nil if no value is associated with key.
 */
- (nullable NSData *)extendedDataForKey:(nonnull NSString *)key;

/**
 Set extended data with a given key.
 
 @discussion You can set any extended data to exist cache key without overriding the existing disk file data.
             On UNIX, the common way for this is to use the Extended file attributes (xattr).
 
 @param extendedData The extended data (pass nil to remove).
 @param key The key with which to associate the value. If nil, this method has no effect.
*/
- (void)setExtendedData:(nullable NSData *)extendedData forKey:(nonnull NSString *)key;

/**
 Removes the value of the specified key in the cache.
 This method may block the calling thread until file delete is finished.
 
 @param key The key identifying the value to be removed. If nil, this method has no effect.
 */
- (void)removeDataForKey:(nonnull NSString *)key;

/**
 Empties the cache.
 This method may block the calling thread until file delete is finished.
 */
- (void)removeAllData;

/**
 Removes the expired data from the cache. You can choose the data to remove based on
 `ageLimit`, `countLimit` and `sizeLimit` options.
 */
- (void)removeExpiredData;

/**
 The cache path for key
 
 @param key A string identifying the value
 @return The cache path for key. Or nil if the key cannot be associated with a path
 */
- (nullable NSString *)cachePathForKey:(nonnull NSString *)key;

/**
 Returns the number of data items in this cache.
 This method may block the calling thread until file read is finished.
 
 @return The total data count.
 */
- (NSUInteger)totalCount;

/**
 Returns the total size (in bytes) of data in this cache.
 This method may block the calling thread until file read is finished.
 
 @return The total data size in bytes.
 */
- (NSUInteger)totalSize;

@end

/**
 The built-in disk cache implementation.
 */
@interface SDDiskCache : NSObject <SDDiskCache>

/**
 Cache Config object - storing all kinds of settings.
 */
@property (nonatomic, strong, readonly, nonnull) SDImageCacheConfig *config;

- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 Move the cache directory from old location to new location, the old location will be removed after finish.
 
 @discussion This method handles several scenarios:
 - If the old location does not exist, does nothing.
 - If the new location does not exist, only performs a directory move.
 - If the new location exists, will move and merge files from the old location.
 - If the new location exists but is not a directory, will remove it and perform a directory move.

 @param srcPath Old location of cache directory
 @param dstPath New location of cache directory
 */
- (void)moveCacheDirectoryFromPath:(nonnull NSString *)srcPath toPath:(nonnull NSString *)dstPath;

@end