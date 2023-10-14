//
//  FXNConfiguration.h
//  Function
//
//  Created by Yusuf Olokoba on 5/27/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

#include <stdint.h>
#include "FXNStatus.h"

#pragma region --Enumerations--
/*!
 @enum FXNAcceleration

 @abstract Hardware acceleration used for predictions.

 @constant FXN_ACCELERATION_DEFAULT
 Use the default acceleration for the given platform.

 @constant FXN_ACCELERATION_CPU
 Use the CPU.
 
 @constant FXN_ACCELERATION_GPU
 Use the GPU.
 
 @constant FXN_ACCELERATION_NPU
 Use the neural processing unit.
 
 @constant FXN_ACCELERATION_ALL
 Use all available acceleration methods including the CPU, GPU, and neural processing units.
*/
enum FXNAcceleration {
    FXN_ACCELERATION_DEFAULT  = 0,
    FXN_ACCELERATION_CPU      = 1 << 0,
    FXN_ACCELERATION_GPU      = 1 << 1,
    FXN_ACCELERATION_NPU      = 1 << 2,
    FXN_ACCELERATION_ALL      = FXN_ACCELERATION_CPU | FXN_ACCELERATION_GPU | FXN_ACCELERATION_NPU
};
typedef enum FXNAcceleration FXNAcceleration;
#pragma endregion


#pragma region --Types--
/*!
 @struct FXNConfiguration

 @abstract Opaque type for predictor configuration.
*/
struct FXNConfiguration;
typedef struct FXNConfiguration FXNConfiguration;
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNCreateConfiguration

 @abstract Create a predictor configuration.

 @discussion Create a predictor configuration.

 @param configuration
 Created configuration. Must not be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNCreateConfiguration (FXNConfiguration** configuration);

/*!
 @function FXNReleaseConfiguration

 @abstract Release the predictor configuration.

 @discussion Release the predictor configuration.

 @param configuration
 Predictor configuration.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNReleaseConfiguration (FXNConfiguration* configuration);
#pragma endregion


#pragma region --Configuration--
/*!
 @function FXNConfigurationSetAcceleration

 @abstract Specify the acceleration used for making predictions.

 @discussion Specify the acceleration used for making predictions.

 @param configuration
 Predictor configuration.

 @param acceleration
 Acceleration used for making predictions predictions.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationSetAcceleration (
    FXNConfiguration* configuration,
    FXNAcceleration acceleration
);

/*!
 @function FXNConfigurationSetDevice

 @abstract Specify the compute device used for ML model inference.

 @discussion Specify the compute device used for ML model inference.

 @param configuration
 Predictor configuration.

 @param device
 Compute device used for ML model inference.
 The type of this device is platform-dependent (see https://docs.fxn.ai).
 Pass `NULL` to use the default compute device.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationSetDevice (
    FXNConfiguration* configuration,
    void* device
);

/*!
 @function FXNCofigurationSetFingerprint

 @abstract Set the predictor fingerprint.

 @discussion Set the predictor fingerprint.
 This is used for caching and optimization.

 @param configuration
 Predictor configuration.

 @param fingerprint
 Predictor fingerprint. Can be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationSetFingerprint (
    FXNConfiguration* configuration,
    const char* fingerprint
);
#pragma endregion