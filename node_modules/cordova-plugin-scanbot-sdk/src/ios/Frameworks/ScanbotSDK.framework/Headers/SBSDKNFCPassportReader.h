//
//  SBSDKNFCPassportReader.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 17.02.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreNFC/CoreNFC.h>
#import "SBSDKNFCDatagroupType.h"
#import "SBSDKNFCDatagroup.h"
#import "SBSDKNFCDatagroupDG1.h"
#import "SBSDKNFCDatagroupDG2.h"
#import "SBSDKNFCPassportReaderError.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKNFCPassportReader;


API_AVAILABLE(ios(13.0))

/** The delegate protocol for SBSDKPassportReader class. */
@protocol SBSDKPassportReaderDelegate<NSObject>

/**
 * Informs the delegate that the reader did connect to the passports NFC chip.
 * @param reader The passport reader instance that established the connection.
 */
- (void)passportReaderDidConnect:(SBSDKNFCPassportReader *)reader;

@optional

/**
 * Informs the delegate that the reader failed to connect to the passports NFC chip.
 * @param reader The passport reader instance that tried to establish the connection.
 */
- (void)passportReaderDidFailToConnect:(SBSDKNFCPassportReader *)reader;

/**
 * Informs the delegate that the reader finished the session with the passports NFC chip.
 * @param reader The passport reader instance that finished the session.
 */
- (void)passportReaderDidFinishSession:(SBSDKNFCPassportReader *)reader;

/**
 * Informs the delegate that the reader cancelled the session with the passports NFC chip.
 * @param reader The passport reader instance that cancelled the session.
 */
- (void)passportReaderDidCancelSession:(SBSDKNFCPassportReader *)reader;

/**
 * Informs the delegate that the reader started reading a data group from the passports NFC chip.
 * @param reader The passport reader instance that started reading the data group.
 * @param type The type of the data group being read.
 */
- (void)passportReader:(SBSDKNFCPassportReader *)reader didStartReadingGroup:(SBSDKNFCDatagroupType *)type;

/**
 * Informs the delegate that the reader finished reading a data group from the passports NFC chip.
 * @param reader The passport reader instance that finished reading the data group.
 * @param type The type of the data group being read.
 */
- (void)passportReader:(SBSDKNFCPassportReader *)reader didFinishReadingGroup:(SBSDKNFCDatagroupType *)type;

/**
 * Informs the delegate that the reader progressed reading a data group from the passports NFC chip.
 * @param reader The passport reader instance that progressed reading the data group.
 * @param progress The progress of reading. Ranges from 0.0 (0%) to 1.0 (100%) read progress.
 */
- (void)passportReader:(SBSDKNFCPassportReader *)reader didProgressReadingGroup:(float)progress;

/**
 * Asks the delegate for the text to display in case an error occures. Optional.
 * If not implemented - english standard strings are applied.
 * @param reader The calling SBSDKNFCPassportReader.
 * @param error Occurred error.
 * @return The localized error string to display. If you return nil - the default values will be used.
 */
- (nullable NSString *)passportReader:(SBSDKNFCPassportReader *)reader
                localizedTextForError:(SBSDKNFCPassportReaderError)error;

@end


API_AVAILABLE(ios(13.0))
/**
 * A class to extract the data from a passport's Near Field Communication (NFC) chip.
 *
 * Notes:
 * - Requires iOS 13.0+
 * - Your app needs to add the "Near Field Communication Tag Reading" entitlement
 * - Your apps info.plist needs to define the passport nfc application ID. To do so
 * add the following entry: "com.apple.developer.nfc.readersession.iso7816.select-identifiers" and as the first element
 * add the passport application ID "A0000002471001"
 */
@interface SBSDKNFCPassportReader : NSObject 

/**
 * @return YES, if passport NFC reading is available on the system, NO otherwise.
 */
+ (BOOL)isPassportReadingAvailable;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * @param passportNumber The passports alphanumerical ID, as printed on the passport.
 * @param birthDate The passport holders birth date.
 * @param expirationDate The passports expiry date
 * @param messsage The initial message being shown on the NFC-scanning UI when NFC reading starts.
 * @param delegate The delegate of the passport reader.
 * @return A newly initialized and ready to use instance of SBSDKNFCPassportReader.
 */
- (instancetype)initWithPassportNumber:(NSString *)passportNumber
                             birthDate:(NSDate *)birthDate
                        expirationDate:(NSDate *)expirationDate
                        initialMessage:(nullable NSString *)messsage
                              delegate:(id<SBSDKPassportReaderDelegate>)delegate;

/**
 * Sets the message being displayed on the NFC-scanning UI.
 * @param message The message to be displayed.
 *
 * Note: Repeated message changes may not be reflected in the UI due to the asynchronous updating. This is
 * a restriction of the underlying Apple API.
 */
- (void)setMessage:(NSString *)message;

/**
 * Enumerates all available data group types on the passports NFC chip and returns them to the completion handler.
 * @param completion The completion handler called when the operation has finished. Passes an array of available
 * data group types.
 *
 * Note: Not all available data groups are accessible/readable with the basic authentication that we are allowed to use.
 * Most often only DG1 and DG2 are accessible.
 */
- (void)enumerateDatagroups:(void(^)(NSArray<SBSDKNFCDatagroupType*>*))completion;


/**
 * Downloads and parses the specified data groups.
 * @param types An array of data group types the receiver should read and parse. Usually this is only DG1 and DG2.
 * @param shouldIgnoreUnavailableGroups If set to NO, then the state when some of requested groups will be missing or unavailable will be treated
 * as an error state and nothing will return. If set to YES, the method will just return available groups, ignoring unavailable.
 * @param completion The completion handler that is called when reading and parsing of the specified data groups has finished.
 * The completion handler is called passing an array of readily parsed data group objects.
 */
- (void)downloadDatagroupsOfType:(NSArray<SBSDKNFCDatagroupType*>*)types
   shouldIgnoreUnavailableGroups:(BOOL)shouldIgnoreUnavailableGroups
                      completion: (void(^)(NSArray<SBSDKNFCDatagroup*>*))completion;

/**
 * Downloads and parses the specified data groups. Unavailable data groups are ignored.
 * @param types An array of data group types the receiver should read and parse. Usually this is only DG1 and DG2.
 * @param completion The completion handler that is called when reading and parsing of the specified data groups has finished.
 * The completion handler is called passing an array of readily parsed data group objects.
 */
- (void)downloadDatagroupsOfType:(NSArray<SBSDKNFCDatagroupType*>*)types
                      completion: (void(^)(NSArray<SBSDKNFCDatagroup*>*))completion;

@end

NS_ASSUME_NONNULL_END
