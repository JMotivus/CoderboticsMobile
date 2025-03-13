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
 * A Image-Asset manager to work like UIKit/AppKit's image cache behavior.
 * 
 * This class provides functionality to load and cache images from Asset Catalogs.
 * Since Apple parses the Asset Catalog compiled file (`Assets.car`) using the private
 * CoreUI.framework, this implementation works with normal bundle files instead.
 */
@interface SDImageAssetManager : NSObject

/**
 * Cache storage for images, using name as key and UIImage as value.
 * Using NSMapTable allows for memory-efficient storage with customizable key/value retention.
 */
@property (nonatomic, strong, readonly) NSMapTable<NSString *, UIImage *> *imageTable;

/**
 * Returns the shared singleton instance of the asset manager.
 *
 * @return The shared asset manager instance.
 */
+ (instancetype)sharedAssetManager;

/**
 * Gets the file path for an asset with the specified name in the given bundle.
 *
 * @param name The name of the asset.
 * @param bundle The bundle containing the asset.
 * @param scale A pointer to store the preferred scale of the asset. Must not be NULL.
 * @return The path to the asset file, or nil if not found.
 */
- (nullable NSString *)getPathForName:(NSString *)name 
                               bundle:(NSBundle *)bundle 
                       preferredScale:(CGFloat *)scale;

/**
 * Retrieves a cached image for the specified name.
 *
 * @param name The name of the image to retrieve.
 * @return The cached image, or nil if not found.
 */
- (nullable UIImage *)imageForName:(NSString *)name;

/**
 * Stores an image in the cache with the specified name.
 *
 * @param image The image to store.
 * @param name The name to associate with the image.
 */
- (void)storeImage:(UIImage *)image forName:(NSString *)name;

@end

NS_ASSUME_NONNULL_END