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
 @struct FXNCreatePredictorFunc
 
 @abstract Predictor creation function.

 @discussion Predictor creation function.

 @param configuration
 Predictor configuration. Can be `NULL`.

 @param predictor
 Created predictor. Must not be `NULL`.
*/
typedef FXNStatus (*FXNCreatePredictorFunc) (
    FXNConfiguration* configuration,
    FXNPredictor** predictor
);

/*!
 @struct FXNReleasePredictorFunc
 
 @abstract Predictor destruction function.

 @discussion Predictor destruction function.

 @param predictor
 Predictor.
*/
typedef FXNStatus (*FXNReleasePredictorFunc) (FXNPredictor* predictor);

/*!
 @struct FXNPredictFunc
 
 @abstract Prediction function.

 @discussion Prediction function.

 @param predictor
 Predictor.

 @param inputs
 Prediction inputs. Must not be `NULL`.

 @param outputs
 Prediction outputs. Must not be `NULL`.
*/
typedef FXNStatus (*FXNPredictFunc) (
    FXNPredictor* predictor,
    FXNValueMap* inputs,
    FXNValueMap** outputs
);
#pragma endregion