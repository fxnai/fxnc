//
//  FXNConfiguration.h
//  Function
//
//  Created by Yusuf Olokoba on 5/27/2023.
//  Copyright © 2024 NatML Inc. All rights reserved.
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
*/
enum FXNAcceleration {
    FXN_ACCELERATION_DEFAULT  = 0,
    FXN_ACCELERATION_CPU      = 1 << 0,
    FXN_ACCELERATION_GPU      = 1 << 1,
    FXN_ACCELERATION_NPU      = 1 << 2,
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
 @function FXNConfigurationGetUniqueID

 @abstract Get a configuration identifier.

 @discussion Get a configuration identifier.

 @param identifier
 Predictor configuration identifier.

 @param size
 Identifier size.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationGetUniqueID (
    char* identifier,
    int32_t size
);

/*!
 @function FXNConfigurationCreate

 @abstract Create a predictor configuration.

 @discussion Create a predictor configuration.

 @param configuration
 Created configuration. MUST NOT be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationCreate (FXNConfiguration** configuration);

/*!
 @function FXNConfigurationRelease

 @abstract Release the predictor configuration.

 @discussion Release the predictor configuration.

 @param configuration
 Predictor configuration.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationRelease (FXNConfiguration* configuration);
#pragma endregion


#pragma region --Configuration--
/*!
 @function FXNConfigurationGetToken

 @abstract Get the configuration token.

 @discussion Get the configuration token.
 This is requried for Function to load the predictor.

 @param configuration
 Predictor configuration.

 @param token
 Destination buffer.

 @param size
 Size of destination buffer.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationGetToken (
    FXNConfiguration* configuration,
    char* token,
    int32_t size
);

/*!
 @function FXNConfigurationSetToken

 @abstract Set the configuration token.

 @discussion Set the configuration token.
 This is requried for Function to load the predictor.

 @param configuration
 Predictor configuration.

 @param token
 Configuration token.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationSetToken (
    FXNConfiguration* configuration,
    const char* token
);

/*!
 @function FXNConfigurationGetResource

 @abstract Get a predictor resource.

 @discussion Get a predictor resource.

 @param configuration
 Predictor configuration.

 @param id
 Resource identifier.

 @param path
 Resource path.

 @param pathLen
 Length of `path` buffer.

 @returns `FXN_OK` if the resource exists. `FXN_ERROR_INVALID_ARGUMENT` if the resource does not exist.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationGetResource (
    FXNConfiguration* configuration,
    const char* id,
    char* path,
    int32_t pathLen
);

/*!
 @function FXNConfigurationSetResource

 @abstract Set a predictor resource.

 @discussion Set a predictor resource.

 @param configuration
 Predictor configuration.

 @param id
 Resource identifier.

 @param type
 Resource type.

 @param path
 Resource path. Passing `NULL` will remove the resource from the configuration.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationSetResource (
    FXNConfiguration* configuration,
    const char* id,
    const char* type,
    const char* path
);

/*!
 @function FXNConfigurationGetAcceleration

 @abstract Get the acceleration used for making predictions.

 @discussion Get the acceleration used for making predictions.

 @param configuration
 Predictor configuration.

 @param acceleration
 Acceleration.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationGetAcceleration (
    FXNConfiguration* configuration,
    FXNAcceleration* acceleration
);

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
 @function FXNConfigurationGetDevice

 @abstract Get the compute device used for ML model inference.

 @discussion Get the compute device used for ML model inference.

 @param configuration
 Predictor configuration.

 @param device
 Compute device used for ML model inference.
 The type of this device is platform-dependent (see https://docs.fxn.ai).
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNConfigurationGetDevice (
    FXNConfiguration* configuration,
    void** device
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
#pragma endregion