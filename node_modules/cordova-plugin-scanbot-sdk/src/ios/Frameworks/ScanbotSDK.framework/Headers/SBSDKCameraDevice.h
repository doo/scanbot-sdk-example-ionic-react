//
//  SBSDKCameraDevice.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 16.11.21.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/** Enum for camera device positions. */
typedef NS_ENUM(NSUInteger, SBSDKCameraDevicePosition) {
    /** The back-facing camera position. */
    SBSDKCameraDevicePositionBack        = 0,

    /** The front-facing camera position. */
    SBSDKCameraDevicePositionFront       = 1
};

/** Enum for camera device types. */
typedef NS_ENUM(NSUInteger, SBSDKCameraDeviceType) {
    /** The wide angle camera type. */
    SBSDKCameraDeviceTypeWide       = 0,

    /** The telephoto camera type. */
    SBSDKCameraDeviceTypeTele       = 1
};

/**
 * The camera device to be used with a SBSDKCameraSession.
 * To retrieve a list of available devices you can pass to many of SDKs classic or RTU-UI component please use
 * the class functions starting with availableDevices...
 */
@interface SBSDKCameraDevice : NSObject

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/** The type of the camera: wide angle or telephoto lens. */
@property(nonatomic, readonly) SBSDKCameraDeviceType deviceType;

/** The position of the camera: front or back side camera. */
@property(nonatomic, readonly) SBSDKCameraDevicePosition devicePosition;

/** The capture device for internal uses. Do not use directly. */
@property(nonatomic, strong, readonly) AVCaptureDevice *device;

/** The name of the camera device. */
@property(nonatomic, readonly) NSString *name;

/**
 * Retrieves a list of all available camera devices sorted by position (front < back) and type (wide < tele).
 * @return An array of available camera devices.
 */
+ (NSArray<SBSDKCameraDevice*> *)availableDevices;

/**
 * Retrieves a list of all available camera devices matching the given position, sorted by type (wide < tele).
 * @param position The position for which the camera devices should be returned.
 * @return An array of available camera devices matching the given position.
 */
+ (NSArray<SBSDKCameraDevice*> *)availableDevicesForPosition:(SBSDKCameraDevicePosition)position;

/**
 * Retrieves a list of all available camera devices matching the given type, sorted by position (front < back).
 * @param type The camera/lens type for which the camera devices should be returned.
 * @return An array of available camera devices matching the given type.
 */
+ (NSArray<SBSDKCameraDevice*> *)availableDevicesForType:(SBSDKCameraDeviceType)type;

/**
 * Retrieves a list of all available camera devices matching the given type and position,
 * sorted by position (front < back) and type (wide < tele).
 * @return An array of available camera devices matching the given type and position.
 */
+ (NSArray<SBSDKCameraDevice*> *)availableDevicesForType:(SBSDKCameraDeviceType)type
                                             andPosition:(SBSDKCameraDevicePosition)position;

/**
 * Returns the default back side camera, which in most cases is the backside, wide angle camera.
 * @return The default back side camera if available. Nil otherwise.
 */
+ (nullable SBSDKCameraDevice *)defaultBackFacingCamera;

/**
 * Returns the default front side camera, which in most cases is the frontside, wide angle camera.
 * @return The default front side camera if available. Nil otherwise.
 */
+ (nullable SBSDKCameraDevice *)defaultFrontFacingCamera;

@end

NS_ASSUME_NONNULL_END
