//
//  FXNFeature.h
//  Function
//
//  Created by Yusuf Olokoba on 5/27/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

#include "FXNFeatureType.h"

#pragma region --Enumerations--
/*!
 @enum FXNFeatureFlags

 @abstract Feature flags.

 @constant FXN_FEATURE_FLAG_NONE
 No flags.

 @constant FXN_FEATURE_FLAG_COPY_DATA
 Copy input tensor data when creating feature.
 When this flag is not set, the feature data MUST remain valid for the lifetime of the created feature.
*/
enum FXNFeatureFlags {
    FXN_FEATURE_FLAG_NONE               = 0,
    FXN_FEATURE_FLAG_COPY_DATA          = 1,
};
typedef enum FXNFeatureFlags FXNFeatureFlags;
#pragma endregion


#pragma region --Types--
/*!
 @struct FXNFeature
 
 @abstract ML model input or output feature.

 @discussion ML model input or output feature.
 This is loosely based on `DLPack::DLTensor`.
*/
struct FXNFeature;
typedef struct FXNFeature FXNFeature;
#pragma endregion


#pragma region --Operations--
/*!
 @function FXNReleaseFeature

 @abstract Release an feature.

 @discussion Release an feature.

 @param feature
 Feature.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNReleaseFeature (FXNFeature* feature);

/*!
 @function FXNFeatureGetType

 @abstract Get the feature type.

 @discussion Get the feature type.

 @param feature
 Feature.

 @param type
 Output feature type.
 This type MUST be released once it is no longer in use.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNFeatureGetType (
    FXNFeature* feature,
    FXNFeatureType** type
);

/*!
 @function FXNFeatureGetData

 @abstract Get the feature data.

 @discussion Get the feature data.

 @param feature
 Feature.

 @returns Opaque pointer to feature data.
*/
FXN_BRIDGE FXN_EXPORT void* FXN_API FXNFeatureGetData (FXNFeature* feature);
#pragma endregion


#pragma region --Constructors--
/*!
 @function FXNCreateArrayFeature

 @abstract Create an array feature from a data buffer.

 @discussion Create an array feature from a data buffer.

 @param data
 Feature data.

 @param shape
 Feature shape.

 @param dims
 Number of dimensions in shape.
 Zero dims indicates a scalar value.

 @param dtype
 Feature data type.

 @param flags
 Feature creation flags.

 @param feature
 Created feature.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNCreateArrayFeature (
    void* data,
    const int32_t* shape,
    int32_t dims,
    FXNDtype dtype,
    FXNFeatureFlags flags,
    FXNFeature** feature
);
#pragma endregion