//
//  FXNModel.h
//  Function
//
//  Created by Yusuf Olokoba on 5/27/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

#include "FXNFeature.h"
#include "FXNModelConfiguration.h"

#pragma region --Types--
/*!
 @struct FXNModel

 @abstract Opaque type for an ML model.
*/
struct FXNModel;
typedef struct FXNModel FXNModel;

/*!
 @abstract Callback invoked with created model.
 
 @param context
 User context provided to the model creation function.
 
 @param model
 ML model. If model creation fails for any reason, this will be `NULL`.
*/
typedef void (*FXNModelCreationHandler) (void* context, FXNModel* model);
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNCreateModel

 @abstract Create an ML model.

 @discussion Create an ML model.

 @param buffer
 ML model data.
 The buffer can be released immediately after calling this function.

 @param bufferSize
 ML model data size.

 @param configuration
 ML model configuration.
 This can be `NULL` in which case reasonable defaults will be used.
 The configuration can be released immediately after calling this function.

 @param handler
 Callback to receive created model.

 @param context
 User context to pass to handler. Can be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNCreateModel (
    const uint8_t* buffer,
    int64_t bufferSize,
    FXNModelConfiguration* configuration,
    FXNModelCreationHandler handler,
    void* context
);

/*!
 @function FXNReleaseModel

 @abstract Release an ML model.

 @discussion Release an ML model.

 @param model
 ML model.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNReleaseModel (FXNModel* model);
#pragma endregion


#pragma region --Metadata--
/*!
 @function FXNModelGetMetadataCount

 @abstract Get the number of metadata keys in a model.

 @discussion Get the number of metadata keys in a model.

 @param model
 ML model.

 @returns Number of metadata keys in the model.
*/
FXN_BRIDGE FXN_EXPORT int32_t FXN_API FXNModelGetMetadataCount (FXNModel* model);

/*!
 @function FXNModelGetMetadataKey

 @abstract Get the metadata key in a model.

 @discussion Get the metadata key in a model.

 @param model
 ML model.

 @param index
 Metadata key index.

 @param key
 Destination UTF-8 encoded key string.

 @param size
 Size of destination buffer.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNModelGetMetadataKey (
    FXNModel* model,
    int32_t index,
    char* key,
    int32_t size
);

/*!
 @function FXNModelGetMetadataValue

 @abstract Get the metadata value for a correspondig key in a model.

 @discussion Get the metadata value for a correspondig key in a model.

 @param model
 ML model.

 @param key
 Metadata key.

 @param value
 Destination UTF-8 encoded value string.

 @param size
 Size of destination buffer.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNModelGetMetadataValue (
    FXNModel* model,
    const char* key,
    char* value,
    int32_t size
);
#pragma endregion


#pragma region --Inspection--
/*!
 @function FXNModelGetInputFeatureCount

 @abstract Get the number of input features in a model.

 @discussion Get the number of input features in a model.

 @param model
 ML model.

 @returns Number of input features in the model.
*/
FXN_BRIDGE FXN_EXPORT int32_t FXN_API FXNModelGetInputFeatureCount (FXNModel* model);

/*!
 @function FXNModelGetInputFeatureType

 @abstract Get the input feature type in a model.

 @discussion Get the input feature type in a model.

 @param model
 ML model.

 @param index
 Input feature index.

 @param type
 Output feature type. This type should be released once it is no longer in use.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNModelGetInputFeatureType (
    FXNModel* model,
    int32_t index,
    FXNFeatureType** type
);

/*!
 @function FXNModelGetOutputFeatureCount

 @abstract Get the number of output features in a model.

 @discussion Get the number of output features in a model.

 @param model
 ML model.

 @returns Number of output features in the model.
*/
FXN_BRIDGE FXN_EXPORT int32_t FXN_API FXNModelGetOutputFeatureCount (FXNModel* model);

/*!
 @function FXNModelGetOutputFeatureType

 @abstract Get the output feature type in a model.

 @discussion Get the output feature type in a model.

 @param model
 ML model.

 @param index
 Output feature index.

 @param type
 Output feature type. This type should be released once it is no longer in use.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNModelGetOutputFeatureType (
    FXNModel* model,
    int32_t index,
    FXNFeatureType** type
);
#pragma endregion


#pragma region --Prediction--
/*!
 @function FXNModelPredict

 @abstract Make a prediction with a model.

 @discussion Make a prediction with a model.

 @param model
 ML model.

 @param inputs
 Input features to run prediction on. The length of this array must match the model's input count.

 @param outputs
 Output features. The length of this array must match the model's output count.
 Each feature MUST be released when no longer needed.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNModelPredict (
    FXNModel* model,
    FXNFeature * const * inputs,
    FXNFeature** outputs
);
#pragma endregion