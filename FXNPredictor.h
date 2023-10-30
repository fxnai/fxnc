//
//  FXNPredictor.h
//  Function
//
//  Created by Yusuf Olokoba on 10/14/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

#include "FXNConfiguration.h"
#include "FXNValueMap.h"

#pragma region --Types--
/*!
 @struct FXNPredictor
 
 @abstract Predictor.

 @discussion Predictor.
*/
struct FXNPredictor;
typedef struct FXNPredictor FXNPredictor;
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNPredictorCreate

 @abstract Create a predictor.

 @discussion Create a predictor.

 @param tag
 Predictor tag.

 @param configuration
 Predictor configuration. Must not be `NULL`.

 @param predictor
 Created predictor. Must not be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNPredictorCreate (
    const char* tag,
    FXNConfiguration* configuration,
    FXNPredictor** predictor
);

/*!
 @function FXNPredictorRelease

 @abstract Release a predictor.

 @discussion Release a predictor.

 @param predictor
 Predictor.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNPredictorRelease (FXNPredictor* predictor);
#pragma endregion


#pragma region --Operations--
/*!
 @function FXNPredictorPredict

 @abstract Make a prediction.

 @discussion Make a prediction.

 @param predictor
 Predictor.

 @param inputs
 Prediction inputs. Must not be `NULL`.

 @param outputs
 Prediction outputs. Must not be `NULL`.
 You MUST release the value map with `FXNValueMapRelease` when no longer needed.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNPredictorPredict (
    FXNPredictor* predictor,
    FXNValueMap* inputs,
    FXNValueMap** outputs
);
#pragma endregion