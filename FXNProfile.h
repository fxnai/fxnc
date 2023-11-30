//
//  FXNProfile.h
//  Function
//
//  Created by Yusuf Olokoba on 11/23/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

#include <stdint.h>
#include "FXNStatus.h"

#pragma region --Types--
/*!
 @struct FXNProfile
 
 @abstract Prediction profile.

 @discussion Prediction profile.
*/
struct FXNProfile;
typedef struct FXNProfile FXNProfile;
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNProfileRelease

 @abstract Release a profile.

 @discussion Release a profile.

 @param profile
 Profile.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNProfileRelease (FXNProfile* profile);
#pragma endregion


#pragma region --Operations--
/*!
 @function FXNProfileGetID

 @abstract Get the prediction ID.

 @discussion Get the prediction ID.

 @param profile
 Prediction profile.

 @param destination
 Destination buffer.

 @param size
 Destination buffer size.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNProfileGetID (
    FXNProfile* profile,
    char* destination,
    int32_t size
);

/*!
 @function FXNProfileGetLatency

 @abstract Get the prediction latency.

 @discussion Get the prediction latency.

 @param profile
 Prediction profile.

 @param latency
 Prediction latency in milliseconds.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNProfileGetLatency (
    FXNProfile* profile,
    double* latency
);

/*!
 @function FXNProfileGetError

 @abstract Get the prediction error.

 @discussion Get the prediction error.

 @param profile
 Prediction profile.

 @param error
 Destination buffer.

 @param size
 Destination buffer size.

 @returns `FXN_OK` if an error has been copied. `FXN_ERROR_INVALID_OPERATION` if no error is present in the profile.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNProfileGetError (
    FXNProfile* profile,
    char* error,
    int32_t size
);

/*!
 @function FXNProfileGetLogs

 @abstract Get the prediction logs.

 @discussion Get the prediction logs.

 @param profile
 Prediction profile.

 @param logs
 Destination buffer.

 @param size
 Destination buffer size.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNProfileGetLogs (
    FXNProfile* profile,
    char* logs,
    int32_t size
);

/*!
 @function FXNProfileGetLogLength

 @abstract Get the prediction log length.

 @discussion Get the prediction log length.

 @param profile
 Prediction profile.

 @param length
 Logs length.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNProfileGetLogLength (
    FXNProfile* profile,
    int32_t* length
);
#pragma endregion