// Auto-generated. Modification will be overwritten.

#import <UIKit/UIKit.h>
#import "SBSDKGenericDocumentWrapper.h"


/** Document type name of the "USACheck" document type. */
extern NSString* _Nonnull const SBSDKCheckDocumentUSACheckDocumentType;

/** Document type name of the "FRACheck" document type. */
extern NSString* _Nonnull const SBSDKCheckDocumentFRACheckDocumentType;

/** Document type name of the "KWTCheck" document type. */
extern NSString* _Nonnull const SBSDKCheckDocumentKWTCheckDocumentType;

/** Document type name of the "AUSCheck" document type. */
extern NSString* _Nonnull const SBSDKCheckDocumentAUSCheckDocumentType;

/** Document type name of the "INDCheck" document type. */
extern NSString* _Nonnull const SBSDKCheckDocumentINDCheckDocumentType;

/** Document type name of the "UnknownCheck" document type. */
extern NSString* _Nonnull const SBSDKCheckDocumentUnknownCheckDocumentType;


/** Normalized full name of the FontType field type in document type "Check". */
extern NSString* _Nonnull const SBSDKCheckDocumentCheckFontTypeFieldNormalizedName;

/** Normalized full name of the RawString field type in document type "Check". */
extern NSString* _Nonnull const SBSDKCheckDocumentCheckRawStringFieldNormalizedName;

/** Normalized full name of the AccountNumber field type in document type "USACheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentUSACheckAccountNumberFieldNormalizedName;

/** Normalized full name of the AuxiliaryOnUs field type in document type "USACheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentUSACheckAuxiliaryOnUsFieldNormalizedName;

/** Normalized full name of the TransitNumber field type in document type "USACheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentUSACheckTransitNumberFieldNormalizedName;

/** Normalized full name of the AccountNumber field type in document type "FRACheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentFRACheckAccountNumberFieldNormalizedName;

/** Normalized full name of the ChequeNumber field type in document type "FRACheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentFRACheckChequeNumberFieldNormalizedName;

/** Normalized full name of the RoutingNumber field type in document type "FRACheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentFRACheckRoutingNumberFieldNormalizedName;

/** Normalized full name of the AccountNumber field type in document type "KWTCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentKWTCheckAccountNumberFieldNormalizedName;

/** Normalized full name of the ChequeNumber field type in document type "KWTCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentKWTCheckChequeNumberFieldNormalizedName;

/** Normalized full name of the SortCode field type in document type "KWTCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentKWTCheckSortCodeFieldNormalizedName;

/** Normalized full name of the AccountNumber field type in document type "AUSCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentAUSCheckAccountNumberFieldNormalizedName;

/** Normalized full name of the AuxDomestic field type in document type "AUSCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentAUSCheckAuxDomesticFieldNormalizedName;

/** Normalized full name of the BSB field type in document type "AUSCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentAUSCheckBSBFieldNormalizedName;

/** Normalized full name of the ExtraAuxDomestic field type in document type "AUSCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentAUSCheckExtraAuxDomesticFieldNormalizedName;

/** Normalized full name of the TransactionCode field type in document type "AUSCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentAUSCheckTransactionCodeFieldNormalizedName;

/** Normalized full name of the AccountNumber field type in document type "INDCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentINDCheckAccountNumberFieldNormalizedName;

/** Normalized full name of the SerialNumber field type in document type "INDCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentINDCheckSerialNumberFieldNormalizedName;

/** Normalized full name of the SortNumber field type in document type "INDCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentINDCheckSortNumberFieldNormalizedName;

/** Normalized full name of the TransactionCode field type in document type "INDCheck". */
extern NSString* _Nonnull const SBSDKCheckDocumentINDCheckTransactionCodeFieldNormalizedName;


/** None. */
@interface SBSDKCheckDocumentCheck : SBSDKGenericDocumentWrapper


/** type of check font. */
@property(readonly, nullable) SBSDKGenericDocumentField *fontType;

/** Detected raw string. */
@property(readonly, nonnull) SBSDKGenericDocumentField *rawString;

@end



/** A check compatible with the ASC X9 standard used in the USA. */
@interface SBSDKCheckDocumentUSACheck : SBSDKGenericDocumentWrapper


/** The name of the wrapped document type. */
- (nonnull NSString *)requiredDocumentType;


/** Account number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *accountNumber;

/** Auxiliary On-Us. */
@property(readonly, nullable) SBSDKGenericDocumentField *auxiliaryOnUs;

/** Transit number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *transitNumber;

@end



/** A check format commonly used in France. */
@interface SBSDKCheckDocumentFRACheck : SBSDKGenericDocumentWrapper


/** The name of the wrapped document type. */
- (nonnull NSString *)requiredDocumentType;


/** Account number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *accountNumber;

/** Cheque number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *chequeNumber;

/** Routing number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *routingNumber;

@end



/** A check format commonly used in Kuwait. */
@interface SBSDKCheckDocumentKWTCheck : SBSDKGenericDocumentWrapper


/** The name of the wrapped document type. */
- (nonnull NSString *)requiredDocumentType;


/** Account number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *accountNumber;

/** Cheque number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *chequeNumber;

/** Sort code. */
@property(readonly, nonnull) SBSDKGenericDocumentField *sortCode;

@end



/** A check compatible with the Australian Paper Clearing System cheque standard. */
@interface SBSDKCheckDocumentAUSCheck : SBSDKGenericDocumentWrapper


/** The name of the wrapped document type. */
- (nonnull NSString *)requiredDocumentType;


/** Account number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *accountNumber;

/** Auxiliary domestic. */
@property(readonly, nullable) SBSDKGenericDocumentField *auxDomestic;

/** BSB. */
@property(readonly, nonnull) SBSDKGenericDocumentField *bsb;

/** Extra auxiliary domestic. */
@property(readonly, nullable) SBSDKGenericDocumentField *extraAuxDomestic;

/** Transaction code. */
@property(readonly, nonnull) SBSDKGenericDocumentField *transactionCode;

@end



/** A check compatible with the CTS-2010 standard issued by the Reserve Bank of India in 2012. */
@interface SBSDKCheckDocumentINDCheck : SBSDKGenericDocumentWrapper


/** The name of the wrapped document type. */
- (nonnull NSString *)requiredDocumentType;


/** Account number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *accountNumber;

/** Serial number. */
@property(readonly, nonnull) SBSDKGenericDocumentField *serialNumber;

/** Sort number. */
@property(readonly, nullable) SBSDKGenericDocumentField *sortNumber;

/** Transaction code. */
@property(readonly, nonnull) SBSDKGenericDocumentField *transactionCode;

@end



/** Root document type. */
@interface SBSDKCheckDocumentRootType : SBSDKGenericDocumentType


/** Not available */
- (nonnull instancetype)init NS_UNAVAILABLE;


/** Not available */
+ (nonnull instancetype)new NS_UNAVAILABLE;


/** Array of all available document root types */
+ (nonnull NSArray<SBSDKCheckDocumentRootType *> *)allDocumentTypes;


/**
 * Creates a strongly-typed wrapper of the given document.
 * Returns nil if the document type is not part of this document schema.
 */
+ (nullable SBSDKGenericDocumentWrapper *)wrap:(nonnull SBSDKGenericDocument *)document;


/** Root type for a A check compatible with the ASC X9 standard used in the USA. */
+ (nonnull instancetype)usaCheck;

/** Root type for a A check format commonly used in France. */
+ (nonnull instancetype)fraCheck;

/** Root type for a A check format commonly used in Kuwait. */
+ (nonnull instancetype)kwtCheck;

/** Root type for a A check compatible with the Australian Paper Clearing System cheque standard. */
+ (nonnull instancetype)ausCheck;

/** Root type for a A check compatible with the CTS-2010 standard issued by the Reserve Bank of India in 2012. */
+ (nonnull instancetype)indCheck;

/** Root type for a A check that doesn't conform to any supported standard. */
+ (nonnull instancetype)unknownCheck;

@end
