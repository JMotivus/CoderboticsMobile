/*
* This file is part of the SDWebImage package.
* (c) Olivier Poitrey <rs@dailymotion.com>
* (c) Fabrice Aneche
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 A category on UIImage that provides extended cache data functionality.
 This allows attaching additional metadata to image objects.
 */
@interface UIImage (ExtendedCacheData)

/**
 Read and Write the extended object and bind it to the image.
 
 This property can hold extra metadata such as:
 - Image's scale factor
 - URL rich link
 - Date information
 - Any other custom metadata
 
 @note The extended object must conform to NSCoding protocol. The object is archived
       using NSKeyedArchiver and NSKeyedUnarchiver when written to disk cache.
 
 @note The disk cache preserves both the image data and extended data with the same cache key.
       For manual query, use the `SDDiskCache` protocol method `extendedDataForKey:` instead.
 
 @note You can specify any object that conforms to NSCoding. When loading an image from
       disk cache, you should verify the extended object class to avoid corrupted data.
 
 @warning This object doesn't need to implement NSSecureCoding (though it's recommended),
          as the implementation allows for arbitrary classes.
 */
@property (nonatomic, strong, nullable) id<NSObject, NSCoding> sd_extendedObject;

@end

NS_ASSUME_NONNULL_END