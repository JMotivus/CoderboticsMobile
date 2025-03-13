/*
* This file is part of the SDWebImage package.
* (c) Olivier Poitrey <rs@dailymotion.com>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#import "SDWebImageCompat.h"

/**
 * Copies all associated objects from a source image to a target image.
 * 
 * This includes all category read/write properties that may have been
 * attached to the source image through Objective-C associated objects.
 *
 * @param source The source UIImage containing the associated objects to copy
 * @param target The target UIImage to which the associated objects will be copied
 */
FOUNDATION_EXPORT void SDImageCopyAssociatedObject(UIImage * _Nullable source, UIImage * _Nullable target);