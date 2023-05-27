//
//  FXNModelConfiguration.h
//  Function
//
//  Created by Yusuf Olokoba on 5/27/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

#include <stdint.h>
#include "FXNAPI.h"

#pragma region --Enumerations--
/*!
 @enum FXNAcceleration

 @abstract Acceleration used for ML model predictions.

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
 @struct FXNModelConfiguration

 @abstract Opaque type for ML model configuration.
*/
struct FXNModelConfiguration;
typedef struct FXNModelConfiguration FXNModelConfiguration;

/*!
 @abstract Callback invoked with created secret.
 
 @param context
 User context provided to the secret creation function.
 
 @param secret
 Predictor session secret. If secret creation fails for any reason, this will be `NULL`.
*/
typedef void (*FXNSecretCreationHandler) (void* context, const char* secret);
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNCreateModelConfiguration

 @abstract Create a model configuration.

 @discussion Create a model configuration.

 @param configuration
 Created configuration. Must not be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNCreateModelConfiguration (FXNModelConfiguration** configuration);

/*!
 @function FXNReleaseModelConfiguration

 @abstract Release the model configuration.

 @discussion Release the model configuration.

 @param configuration
 Model configuration.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNReleaseModelConfiguration (FXNModelConfiguration* configuration);
#pragma endregion


#pragma region --Configuration--
/*!
 @function FXNModelConfigurationSetAcceleration

 @abstract Specify the acceleration used for making predictions.

 @discussion Specify the acceleration used for making predictions.

 @param configuration
 Model configuration.

 @param acceleration
 Acceleration used for making predictions predictions.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNModelConfigurationSetAcceleration (
    FXNModelConfiguration* configuration,
    FXNAcceleration acceleration
);

/*!
 @function FXNModelConfigurationSetDevice

 @abstract Specify the compute device used for ML model predictions.

 @discussion Specify the compute device used for ML model predictions.

 @param configuration
 Model configuration.

 @param device
 Compute device used for ML model predictions.
 The type of this device is platform-dependent (see https://docs.fxn.ai).
 Pass `NULL` to use the default compute device.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNModelConfigurationSetDevice (
    FXNModelConfiguration* configuration,
    void* device
);

/*!
 @function FXNModelCofigurationSetFingerprint

 @abstract Set the predictor fingerprint.

 @discussion Set the predictor fingerprint.
 This is used for caching and optimization.

 @param configuration
 Model configuration.

 @param fingerprint
 Predictor fingerprint. Can be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNModelConfigurationSetFingerprint (
    FXNModelConfiguration* configuration,
    const char* fingerprint
);
#pragma endregion


#pragma region --Secret--
/*!
 @function NMLModelConfigurationCreateSecret

 @abstract Create a prediction secret.

 @discussion Create a predictor secret.
 This secret is sent to Function to securely create a model that can be loaded on the device.

 @param handler
 Callback to receive the created secret.

 @param context
 User context to pass to handler. Can be `NULL`.
*/
NML_BRIDGE NML_EXPORT void NML_API NMLModelConfigurationCreateSecret (
    NMLSecretCreationHandler handler,
    void* context
);
#pragma endregion