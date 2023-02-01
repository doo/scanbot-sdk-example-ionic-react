//
//  SBSDKPayFormScanner.h
//  Scanbot SDK
//
//  Created by Sebastian Husche on 21.04.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

#pragma mark - SBSDKPayFormScannerRecognitionMode

/**
 * An enumeration describing the recognition mode of the scanner.
 */
typedef NS_ENUM(NSInteger, SBSDKPayFormScannerRecognitionMode) {
    
    /** Recognize the payform ignoring QR code if present. */
    SBSDKPayFormScannerRecognitionModeTextForm,
    
    /** Recognize and parse the QR code if present ignoring the payform. */
    SBSDKPayFormScannerRecognitionModeQROnly,
    
    /** Fetch information from both payform and QR code. */
    SBSDKPayFormScannerRecognitionModeMixed
};

#pragma mark - SBSDKPayFormTokenType

/**
 * An enumeration describing the types of tokens the SBSDKPayFormScanner can detect and recognize.
 */
typedef NS_ENUM(NSInteger, SBSDKPayFormTokenType) {
    
    /** The name of the payments receiver. */
    SBSDKPayFormTokenTypeReceiver,
    
    /** The IBAN of the payments receiver. */
    SBSDKPayFormTokenTypeIBAN,
    
    /** The BIC of the payments receiver. */
    SBSDKPayFormTokenTypeBIC,
    
    /** The bank name of the payments receiver. */
    SBSDKPayFormTokenTypeBankName,
    
    /** The amount of money being transferred. */
    SBSDKPayFormTokenTypeAmount,
    
    /** The reference number or text. */
    SBSDKPayFormTokenTypeReferenceNumber,
    
    /** Second line for reference number */
    SBSDKPayFormTokenTypeReferenceNumber2,
    
    /** The name of the payment sender */
    SBSDKPayFormTokenTypeSender,
    
    /** The IBAN of the payment sender */
    SBSDKPayFormTokenTypeSenderIBAN,
    
    /** Undefined type type */
    SBSDKPayFormTokenTypeUnknown
};

#pragma mark - SBSDKPayFormToken

/**
 * Describes the position and the type of a text box within the image being detected or recognized.
 */
@interface SBSDKPayFormToken : NSObject

/** The rectangle of the receiver marking the area on the perspective corrected and cropped image. */
@property (nonatomic, assign, readonly) CGRect rect;

/** The receivers type. */
@property (nonatomic, assign, readonly) SBSDKPayFormTokenType type;

/** A debug-string like textual representation of the receiver. **/
@property (nonatomic, copy, readonly, nullable) NSString *stringValue;

@end


#pragma mark - SBSDKPayFormRecognizedField

/**
 * Resulting element of the SBSDKPayFormScanners recognizer.
 * Holds a token and its recognized text value after recognition.
 */
@interface SBSDKPayFormRecognizedField : NSObject

/** The receivers token. */
@property (nonatomic, strong, readonly, nonnull) SBSDKPayFormToken *token;

/** The recognized text for the receivers token. */
@property (nonatomic, copy, readonly, nullable) NSString *value;

/** A debug-string like textual representation of the receiver. **/
@property (nonatomic, copy, readonly, nullable) NSString *stringValue;
@end


#pragma mark - SBSDKPayFormRecognitionResult

/**
 * Result class of SBSDKPayFormScanners recognizer part. Encapsulates the recognized text fields.
 */
@interface SBSDKPayFormRecognitionResult : NSObject

/** Recognition result state */
@property (nonatomic, readonly) BOOL recognitionSuccessful;

/** NSArray of SBSDKPayFormRecognizedField objects as the result of the recognizer. */
@property (nonatomic, readonly, nonnull) NSArray<SBSDKPayFormRecognizedField *> *recognizedFields;

@end


#pragma mark - SBSDKPayFormScanner

/**
 * A class to detect and recognize SEPA payforms on UIImage or CMSampleBufferRef.
 * The larger the image the better the recognition results. Images are rotated accordingly to either the UIImage
 * imageOrientation property or the given video orientation.
 * Detection and recognition are successful only if the rotated image has natural orientation.
 */
@interface SBSDKPayFormScanner : NSObject

/**
 * Recognizes the bank transfer form fields in the given UIImage.
 * @param image The image to recognize a payform on.
 * @return The recognizers result.
 */
- (nullable SBSDKPayFormRecognitionResult *)recognizeFromImage:(nonnull UIImage *)image;

/**
 * Recognizes the bank transfer form fields in the given CMSampleBufferRef.
 * @param sampleBuffer The CMSampleBuffer to recognize a payform on.
 * @param videoOrientation The orientation the sample buffer is taken with.
 * @return The recognizers result.
 */
- (nullable SBSDKPayFormRecognitionResult *)recognizeFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer
                                                          orientation:(AVCaptureVideoOrientation)videoOrientation;

/**
 * Sets the recognition mode of the scanner.
 * @param mode New recognition mode.
 */
- (void)setRecognitionMode:(SBSDKPayFormScannerRecognitionMode)mode;

@end

