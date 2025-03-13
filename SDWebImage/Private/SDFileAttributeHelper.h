//
//  This file is from https://gist.github.com/zydeco/6292773
//
//  Created by Jesús A. Álvarez on 2008-12-17.
//  Copyright 2008-2009 namedfork.net. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * File Extended Attribute (xattr) helper methods
 * Provides utility methods for working with extended file attributes in macOS/iOS
 */
@interface SDFileAttributeHelper : NSObject

/**
 * Returns an array of extended attribute names for the specified path
 *
 * @param path The file path to examine
 * @param follow Whether to follow symbolic links
 * @param err On return, contains any error that occurred
 * @return Array of attribute names or nil if an error occurred
 */
+ (nullable NSArray<NSString *> *)extendedAttributeNamesAtPath:(NSString *)path 
                                                  traverseLink:(BOOL)follow 
                                                         error:(NSError **)err;

/**
 * Checks if a specific extended attribute exists at the given path
 *
 * @param name The name of the extended attribute
 * @param path The file path to examine
 * @param follow Whether to follow symbolic links
 * @param err On return, contains any error that occurred
 * @return YES if the attribute exists, NO otherwise
 */
+ (BOOL)hasExtendedAttribute:(NSString *)name 
                      atPath:(NSString *)path 
                traverseLink:(BOOL)follow 
                       error:(NSError **)err;

/**
 * Retrieves the value of a specific extended attribute at the given path
 *
 * @param name The name of the extended attribute
 * @param path The file path to examine
 * @param follow Whether to follow symbolic links
 * @param err On return, contains any error that occurred
 * @return The attribute value as NSData or nil if an error occurred
 */
+ (nullable NSData *)extendedAttribute:(NSString *)name 
                               atPath:(NSString *)path 
                         traverseLink:(BOOL)follow 
                                error:(NSError **)err;

/**
 * Sets the value of a specific extended attribute at the given path
 *
 * @param name The name of the extended attribute
 * @param value The value to set
 * @param path The file path to modify
 * @param follow Whether to follow symbolic links
 * @param overwrite Whether to overwrite existing attribute
 * @param err On return, contains any error that occurred
 * @return YES if successful, NO otherwise
 */
+ (BOOL)setExtendedAttribute:(NSString *)name 
                       value:(NSData *)value 
                      atPath:(NSString *)path 
                traverseLink:(BOOL)follow 
                   overwrite:(BOOL)overwrite 
                       error:(NSError **)err;

/**
 * Removes a specific extended attribute from the given path
 *
 * @param name The name of the extended attribute
 * @param path The file path to modify
 * @param follow Whether to follow symbolic links
 * @param err On return, contains any error that occurred
 * @return YES if successful, NO otherwise
 */
+ (BOOL)removeExtendedAttribute:(NSString *)name 
                         atPath:(NSString *)path 
                   traverseLink:(BOOL)follow 
                          error:(NSError **)err;

@end

NS_ASSUME_NONNULL_END