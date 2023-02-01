//
//  SBSDKUIDocument.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 13.06.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIPage.h"

/**
 A thread-safe, mutable container for scanned pages of type 'SBSDKUIPage'.
 */
@interface SBSDKUIDocument : NSObject

/** The number of pages the receiver contains. */
- (NSInteger)numberOfPages;

/**
 * Returns the page object at the given index. No boundary checks.
 * @param index The valid index of the page.
 * @return The found page object.
 */
- (SBSDKUIPage *_Nullable)pageAtIndex:(NSInteger)index;

/**
 * Returns the page object with the given page file ID or nil,
 * if the receiver does not contain a page with the given ID.
 * @param uuid The unique ID of a page.
 * @return The found page object or nil.
 */
- (SBSDKUIPage *_Nullable)pageWithPageFileID:(nonnull NSUUID *)uuid;

/**
 * Returns the index of the page object with the given page file ID or NSNotFound,
 * if the receiver does not contain a page with the given ID.
 * @param uuid The unique ID of a page.
 * @return The found page object or nil.
 */
- (NSInteger)indexOfPageWithPageFileID:(nonnull NSUUID *)uuid;

/**
 * Appends a page to the receiver.
 * @param page The page object to be added.
 * @return YES, if the page was successfully added,
 * NO otherwise or if the receiver already contains a page with the same ID.
 */
- (BOOL)addPage:(nonnull SBSDKUIPage *)page;

/**
 * Inserts a page into the receiver at the given position. No boundary checks.
 * @param page The page object to be inserted.
 * @param index The valid index where the page is being inserted.
 * @return YES, if the page was successfully inserted,
 * NO otherwise or if the receiver already contains a page with the same ID.
 */
- (BOOL)insertPage:(nonnull SBSDKUIPage *)page atIndex:(NSInteger)index;

/**
 * Removes the page at the given index from the receiver. No boundary checks.
 * @param index The valid index of the page to be removed.
 */
- (void)removePageAtIndex:(NSInteger)index;

/**
 * Replaces the page at the given index with the given page. No boundary checks.
 * @param index The valid index of the page to be replaced.
 * @param page The page that should be inserted.
 * @return YES, if the page was successfully replaced,
 * NO otherwise or if the receiver already contains a page with the same ID.
 */
- (BOOL)replacePageAtIndex:(NSInteger)index withPage:(nonnull SBSDKUIPage *)page;

@end
