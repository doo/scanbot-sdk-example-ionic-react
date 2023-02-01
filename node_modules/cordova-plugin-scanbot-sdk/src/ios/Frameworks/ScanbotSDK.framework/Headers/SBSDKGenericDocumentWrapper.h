#import <UIKit/UIKit.h>
#import "SBSDKGenericDocument.h"

/** Base class for strongly-typed SBSDKGenericDocument wrappers */
@interface SBSDKGenericDocumentWrapper : NSObject

/** Initializes a new wrapper of the given document. Returns nil if self.requiredDocumentType is not nil and is not equal to the document's type name. */
- (nullable instancetype)initWithGenericDocument:(nullable SBSDKGenericDocument*)document;

/** The required type of the wrapped document. Nil if this wrapper can wrap more than one type of document. */
- (nullable NSString *)requiredDocumentType;

/** The wrapped generic document. */
@property (nonnull, readonly) SBSDKGenericDocument* document;

@end
