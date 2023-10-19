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

/*!
 @struct FXNPredictorCreateFunc
 
 @abstract Predictor creation function.

 @discussion Predictor creation function.

 @param configuration
 Predictor configuration. Can be `NULL`.

 @param predictor
 Created predictor. Must not be `NULL`.
*/
typedef FXNStatus (*FXNPredictorCreateFunc) (
    FXNConfiguration* configuration,
    FXNPredictor** predictor
);

/*!
 @struct FXNPredictorReleaseFunc
 
 @abstract Predictor destruction function.

 @discussion Predictor destruction function.

 @param predictor
 Predictor.
*/
typedef FXNStatus (*FXNPredictorReleaseFunc) (FXNPredictor* predictor);

/*!
 @struct FXNPredictorPredictFunc
 
 @abstract Prediction function.

 @discussion Prediction function.

 @param predictor
 Predictor.

 @param inputs
 Prediction inputs. Must not be `NULL`.

 @param outputs
 Prediction outputs. Must not be `NULL`.
*/
typedef FXNStatus (*FXNPredictorPredictFunc) (
    FXNPredictor* predictor,
    FXNValueMap* inputs,
    FXNValueMap** outputs
);
#pragma endregion