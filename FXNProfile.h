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
 Destination buffer. Can be `NULL`.

 @param errorLen
 Size of destination buffer. Must NOT be `NULL`.
 When `error` is `NULL`, this contains the length of the `error` on return.
 When `error` is not `NULL`, this contains the number of characters written to `error`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNProfileGetError (
    FXNProfile* profile,
    char* error,
    int32_t* errorLen
);

/*!
 @function FXNProfileGetLogs

 @abstract Get the prediction error.

 @discussion Get the prediction error.

 @param profile
 Prediction profile.

 @param logs
 Destination buffer.

 @param logsLen
 Size of destination buffer. Must NOT be `NULL`.
 When `logs` is `NULL`, this contains the length of the `logs` on return.
 When `logs` is not `NULL`, this contains the number of characters written to `logs`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNProfileGetLogs (
    FXNProfile* profile,
    char* logs,
    int32_t* logsLen
);
#pragma endregion