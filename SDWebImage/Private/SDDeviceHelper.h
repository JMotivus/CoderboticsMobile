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
 * Helper class providing device-specific information about hardware and display capabilities.
 * Used throughout SDWebImage to make decisions based on device constraints.
 */
@interface SDDeviceHelper : NSObject

#pragma mark - Memory Information

/**
 * Returns the total physical memory available on the device in bytes.
 * @return Total memory in bytes
 */
+ (NSUInteger)totalMemory;

/**
 * Returns the current free memory available on the device in bytes.
 * @return Free memory in bytes
 */
+ (NSUInteger)freeMemory;

#pragma mark - Display Information

/**
 * Returns the main screen's scale factor.
 * @return Screen scale (1.0 for non-Retina, 2.0 or 3.0 for Retina displays)
 */
+ (double)screenScale;

/**
 * Returns the current Effective Display Resolution (EDR) for the screen.
 * @return Current EDR value
 */
+ (double)screenEDR;

/**
 * Returns the maximum Effective Display Resolution (EDR) supported by the screen.
 * @return Maximum supported EDR value
 */
+ (double)screenMaxEDR;

@end

NS_ASSUME_NONNULL_END