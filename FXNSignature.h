//
//  FXNSignature.h
//  Function
//
//  Created by Yusuf Olokoba on 5/27/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "FXNStatus.h"

#pragma region --Enumerations--
/*!
 @enum FXNDtype

 @abstract Parameter type.

 @constant FXN_DTYPE_NULL
 Type is `null` or undefined.

 @constant FXN_DTYPE_INT8
 Type is a `int8_t` in C/C++ and `sbyte` in C#.

 @constant FXN_DTYPE_INT16
 Type is `int16_t` in C/C++ and `short` in C#.

 @constant FXN_DTYPE_INT32
 Type is `int32_t` in C/C++ and `int` in C#.

 @constant FXN_DTYPE_INT64
 Type is `int64_t` in C/C++ and `long` in C#.

 @constant FXN_DTYPE_UINT8
 Type is `uint8_t` in C/C++ and `byte` in C#.

 @constant FXN_DTYPE_UINT16
 Type is a `uint16_t` in C/C++ and `ushort` in C#.

 @constant FXN_DTYPE_UINT32
 Type is a `uint32_t` in C/C++ and `uint` in C#.

 @constant FXN_DTYPE_UINT64
 Type is a `uint64_t` in C/C++ and `ulong` in C#.

 @constant FXN_DTYPE_FLOAT16
 Type is a generic half-precision float.

 @constant FXN_DTYPE_FLOAT32
 Type is `float` in C/C++/C#.

 @constant FXN_DTYPE_FLOAT64
 Type is `double` in C/C++/C#.

 @constant FXN_DTYPE_BOOL
 Type is a `bool` in C/C++/C#.

 @constant FXN_DTYPE_STRING
 Type is `std::string` in C++ and `string` in C#.

 @constant FXN_DTYPE_LIST
 Type is a JSON-serializable list.

 @constant FXN_DTYPE_DICT
 Type is a JSON-serializable dictionary.

 @constant FXN_DTYPE_IMAGE
 Type is an image pixel buffer. This MUST always be `RGBA8888` in memory.

 @constant FXN_DTYPE_BINARY
 Type is a binary blob.
*/
enum FXNDtype {
    FXN_DTYPE_NULL      = 0,
    FXN_DTYPE_FLOAT16   = 1,
    FXN_DTYPE_FLOAT32   = 2,
    FXN_DTYPE_FLOAT64   = 3,
    FXN_DTYPE_INT8      = 4,
    FXN_DTYPE_INT16     = 5,
    FXN_DTYPE_INT32     = 6,
    FXN_DTYPE_INT64     = 7,
    FXN_DTYPE_UINT8     = 8,
    FXN_DTYPE_UINT16    = 9,
    FXN_DTYPE_UINT32    = 10,
    FXN_DTYPE_UINT64    = 11,
    FXN_DTYPE_BOOL      = 12,
    FXN_DTYPE_STRING    = 13,
    FXN_DTYPE_LIST      = 14,
    FXN_DTYPE_DICT      = 15,
    FXN_DTYPE_IMAGE     = 16,
    FXN_DTYPE_BINARY    = 17,
};
typedef enum FXNDtype FXNDtype;
#pragma endregion


#pragma region --Types--
/*!
 @struct FXNParameter
 
 @abstract Predictor parameter.

 @discussion Predictor parameter.
 This describes a value that is consumed or produced by a predictor.
*/
struct FXNParameter;
typedef struct FXNParameter FXNParameter;
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNCreateParameter

 @abstract Create a parameter.

 @discussion Create a parameter

 @param name
 Parameter name.

 @param type
 Parameter type.

 @param dims
 Parameter dimensions.
 Use `0` for scalar values and `-1` for unknown or undefined dims.

 @param shape
 Parameter shape.
 This must contain at least `dims` integers when specified.
 This can be `NULL` for parameters that do not describe tensors.

 @param parameter
 Created parameter
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNCreateParameter (
    const char* name,
    FXNDtype type,
    int32_t dims,
    const int32_t* shape,
    FXNParameter** parameter
);

/*!
 @function FXNReleaseParameter

 @abstract Release a parameter.

 @discussion Release a parameter

 @param parameter
 Parameter.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNReleaseParameter (FXNParameter* parameter);
#pragma endregion


#pragma region --Operations--
/*!
 @function FXNParameterGetName

 @abstract Get the name of a given parameter.

 @discussion Get the name of a given parameter.

 @param parameter
 Parameter

 @param name
 Destination UTF-8 string.

 @param size
 Size of destination buffer in bytes.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNParameterGetName (
    FXNParameter* parameter,
    char* name,
    int32_t size
);

/*!
 @function FXNParameterGetDtype

 @abstract Get the data type of a given parameter.

 @discussion Get the data type of a given parameter.

 @param parameter
 Parameter.

 @param type
 Parameter data type.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNParameterGetDtype (
    FXNParameter* parameter,
    FXNDtype* type
);

/*!
 @function FXNParameterGetDimensions

 @abstract Get the number of dimensions for a given parameter.

 @discussion Get the number of dimensions for a given parameter.
 If the type is not a tensor, this function will return zero.

 @param parameter
 Parameter.

 @param dimensions
 Number of dimensions for a given parameter.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNParameterGetDimensions (
    FXNParameter* parameter,
    int32_t* dimensions
);

/*!
 @function FXNParameterGetShape

 @abstract Get the shape of a given parameter.

 @discussion Get the shape of a given parameter.

 @param parameter
 Parameter.

 @param shape
 Destination shape array.

 @param shapeLen
 Length of the destination array.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNParameterGetShape (
    FXNParameter* parameter,
    int32_t* shape,
    int32_t shapeLen
);

/*!
 @function FXNParameterGetOptional

 @abstract Get whether a given parameter is optional.

 @discussion Get whether a given parameter is optional.

 @param parameter
 Parameter.

 @param optional
 Whether the parameter is optional.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNParameterGetOptional (
    FXNParameter* parameter,
    bool* optional
);
#pragma endregion