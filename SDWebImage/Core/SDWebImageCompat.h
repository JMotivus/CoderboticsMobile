/*
 * This file is part of the SDWebImage package.
 * (c) Olivier Poitrey <rs@dailymotion.com>
 * (c) Jamie Pinkham
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#import <TargetConditionals.h>

#ifdef __OBJC_GC__
    #error SDWebImage does not support Objective-C Garbage Collection
#endif

// MARK: - Platform Detection

/**
 * Platform detection macros
 * Each macro is defined as 1 when the code is running on that platform, 0 otherwise
 */

// macOS detection
#define SD_MAC (TARGET_OS_OSX ? 1 : 0)

// iOS detection
#define SD_IOS (TARGET_OS_IOS ? 1 : 0)

// tvOS detection
#define SD_TV (TARGET_OS_TV ? 1 : 0)

// watchOS detection
#define SD_WATCH (TARGET_OS_WATCH ? 1 : 0)

// visionOS detection (Xcode 14+ support)
#ifdef TARGET_OS_VISION
    #define SD_VISION (TARGET_OS_VISION ? 1 : 0)
#else
    #define SD_VISION 0
#endif

// UIKit availability check
// iOS/tvOS/visionOS are very similar, UIKit exists on all these platforms
// Note: watchOS also has UIKit, but it's very limited
#define SD_UIKIT ((SD_IOS || SD_TV || SD_VISION) ? 1 : 0)

// MARK: - Platform-specific Imports and Type Definitions

#if SD_MAC
    // macOS - AppKit
    #import <AppKit/AppKit.h>
    
    // Map UIKit types to AppKit equivalents
    #ifndef UIImage
        #define UIImage NSImage
    #endif
    #ifndef UIImageView
        #define UIImageView NSImageView
    #endif
    #ifndef UIView
        #define UIView NSView
    #endif
    #ifndef UIColor
        #define UIColor NSColor
    #endif
#else
    #if SD_UIKIT
        // iOS/tvOS/visionOS - UIKit
        #import <UIKit/UIKit.h>
    #endif
    
    #if SD_WATCH
        // watchOS - WatchKit
        #import <WatchKit/WatchKit.h>
        
        // Map UIKit types to WatchKit equivalents
        #ifndef UIView
            #define UIView WKInterfaceObject
        #endif
        #ifndef UIImageView
            #define UIImageView WKInterfaceImage
        #endif
    #endif
#endif

// MARK: - Compatibility Macros

// Ensure NS_ENUM is defined for older compilers
#ifndef NS_ENUM
    #define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
#endif

// Ensure NS_OPTIONS is defined for older compilers
#ifndef NS_OPTIONS
    #define NS_OPTIONS(_type, _name) enum _name : _type _name; enum _name : _type
#endif

// Helper for safely dispatching to the main queue
#ifndef dispatch_main_async_safe
    #define dispatch_main_async_safe(block) \
        if (dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL) == dispatch_queue_get_label(dispatch_get_main_queue())) { \
            block(); \
        } else { \
            dispatch_async(dispatch_get_main_queue(), block); \
        }
    #pragma clang deprecated(dispatch_main_async_safe, "Use SDCallbackQueue instead")
#endif