/*
* This file is part of the SDWebImage package.
* (c) Olivier Poitrey <rs@dailymotion.com>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#import "SDWebImageCompat.h"

#if SD_MAC

#import <QuartzCore/QuartzCore.h>

/**
 * Creates a media timing function based on the provided animation options.
 *
 * @param options The animation options to use for creating the timing function.
 * @return A CAMediaTimingFunction instance based on the specified options, or nil if not applicable.
 */
FOUNDATION_EXPORT CAMediaTimingFunction * _Nullable SDTimingFunctionFromAnimationOptions(SDWebImageAnimationOptions options);

/**
 * Creates a transition animation based on the provided animation options.
 *
 * @param options The animation options to use for creating the transition.
 * @return A CATransition instance configured with the specified options, or nil if not applicable.
 */
FOUNDATION_EXPORT CATransition * _Nullable SDTransitionFromAnimationOptions(SDWebImageAnimationOptions options);

#endif