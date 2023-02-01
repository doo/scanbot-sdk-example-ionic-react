//
//  SBSDKNFCDatagroupDG2.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 07.05.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import "SBSDKNFCDatagroup.h"
#import <UIKit/UIKit.h>

/**
* Data group 2 or DG2.
* Contains visual biometric data of the passports holder.
*/
@interface SBSDKNFCDatagroupDG2 : SBSDKNFCDatagroup

/** The number of images. */
@property(nonatomic, readonly) NSInteger numberOfImages;

/** The version number. */
@property(nonatomic, readonly) NSInteger version;

/** The length of the record. */
@property(nonatomic, readonly) NSInteger lengthOfRecord;

/** The number of facial images. */
@property(nonatomic, readonly) NSInteger numberOfFacialImages;

/** The length of the facial record. */
@property(nonatomic, readonly) NSInteger lengthOfFacialRecord;

/** The number of feature points in the facial record. */
@property(nonatomic, readonly) NSInteger numberOfFeaturePoints;

/** The gender of the holder. */
@property(nonatomic, readonly) NSInteger gender;

/** The eye color of the holder. */
@property(nonatomic, readonly) NSInteger eyeColor;

/** The hair color of the holder. */
@property(nonatomic, readonly) NSInteger hairColor;

/** A mask describing the features. */
@property(nonatomic, readonly) NSInteger featureMask;

/** The expression of the holder. */
@property(nonatomic, readonly) NSInteger expression;

/** The angle of the holders pose. */
@property(nonatomic, readonly) NSInteger poseAngle;

/** The uncertainty of the angle of the holders pose. */
@property(nonatomic, readonly) NSInteger poseAngleUncertainty;

/** The type of the facial image. */
@property(nonatomic, readonly) NSInteger faceImageType;

/** The type of the facial image data. */
@property(nonatomic, readonly) NSInteger imageDataType;

/** The width in pixels of the facial image. */
@property(nonatomic, readonly) NSInteger imageWidth;

/** The height in pixels of the facial image. */
@property(nonatomic, readonly) NSInteger imageHeight;

/** The color space of the facial image. */
@property(nonatomic, readonly) NSInteger imageColorSpace;

/** The source type. */
@property(nonatomic, readonly) NSInteger sourceType;

/** The device type. */
@property(nonatomic, readonly) NSInteger deviceType;

/** The quality of the facial image. */
@property(nonatomic, readonly) NSInteger quality;

/** The actual image data of the facial image. Can be JPEG or JPEG2000. */
@property(nonatomic, readonly) NSData *imageData;

/** The UIImage representation of the facial image. */
@property(nonatomic, readonly) UIImage *image;

@end
