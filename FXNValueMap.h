//
//  FXNValueMap.h
//  Function
//
//  Created by Yusuf Olokoba on 10/14/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

#include "FXNValue.h"

#pragma region --Types--
/*!
 @struct FXNValueMap
 
 @abstract Predictor value map.

 @discussion Predictor value map.
*/
struct FXNValueMap;
typedef struct FXNValueMap FXNValueMap;
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNCreateValueMap

 @abstract Create a prediction value map.

 @discussion Create a prediction value map.

 @param map
 Created value map. Must not be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNCreateValueMap (FXNValueMap** map);

/*!
 @function FXNReleaseValueMap

 @abstract Release the prediction value map.

 @discussion Release the prediction value map.
 This releases all values currently within the map.

 @param map
 Prediction value map.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNReleaseValueMap (FXNValueMap* map);
#pragma endregion


#pragma region --Operations--
/*!
 @function FXNValueMapGetSize

 @abstract Get the size of the value map.

 @discussion Get the size of the value map.

 @param map
 Prediction value map.

 @param size
 Output size. Must not be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueMapGetSize (
    FXNValueMap* map,
    int32_t* size
);

/*!
 @function FXNValueMapGetKey

 @abstract Get the key at a given index in the value map.

 @discussion Get the key at a given index in the value map.

 @param map
 Prediction value map.

 @param index
 Key index. Must be less than the value map size.

 @param key
 Destination UTF-8 encoded key string.

 @param size
 Size of destination buffer.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueMapGetKey (
    FXNValueMap* map,
    int32_t index,
    char* key,
    int32_t size
);

/*!
 @function FXNValueMapGetValue

 @abstract Get the value for a given key in the value map.

 @discussion Get the value for a given key in the value map.

 @param map
 Prediction value map.

 @param key
 Value key.

 @param value
 Output value. Must not be `NULL`.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueMapGetValue (
    FXNValueMap* map,
    const char* key,
    FXNValue** value
);

/*!
 @function FXNValueMapSetValue

 @abstract Set the value for a given key in the value map.

 @discussion Set the value for a given key in the value map.

 @param map
 Prediction value map.

 @param key
 Value key.

 @param value
 Value. Pass `NULL` to remove the value from the map if present.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueMapSetValue (
    FXNValueMap* map,
    const char* key,
    FXNValue* value
);
#pragma endregion