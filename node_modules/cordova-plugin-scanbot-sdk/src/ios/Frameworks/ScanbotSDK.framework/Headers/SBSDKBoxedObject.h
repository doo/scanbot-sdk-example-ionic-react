//
//  SBSDKBoxedObject.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 03.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A protocol for drawing boxes with SBSDKBoxesLayer.
 * Any class that has a drawable rectangular component and should be drawn into a SBSDKBoxesLayer
 * must implement this protocol.
 */
@protocol SBSDKBoxedObject <NSObject>

/**
 * The objects drawable (bounding) rectangle in view/layer space.
 */
@property (nonatomic, readonly) CGRect boundingRect;

@end

NS_ASSUME_NONNULL_END
