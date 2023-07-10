//
//  FXNFeatureType.h
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
 @enum FXNDtype

 @abstract Feature data type.

 @constant FXN_DTYPE_NULL
 Type is `null` or invalid.

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
 Type is a sequence.

 @constant FXN_DTYPE_DICT
 Type is a dictionary.

 @constant FXN_DTYPE_IMAGE
 Type is an encoded image.

 @constant FXN_DTYPE_BINARY
 Type is a binary blob.
*/
enum FXNDtype {
    FXN_DTYPE_NULL      = 0,
    FXN_DTYPE_INT8      = 10,
    FXN_DTYPE_INT16     = 2,
    FXN_DTYPE_INT32     = 3,
    FXN_DTYPE_INT64     = 4,
    FXN_DTYPE_UINT8     = 1,
    FXN_DTYPE_UINT16    = 11,
    FXN_DTYPE_UINT32    = 12,
    FXN_DTYPE_UINT64    = 13,
    FXN_DTYPE_FLOAT16   = 14,
    FXN_DTYPE_FLOAT32   = 5,
    FXN_DTYPE_FLOAT64   = 6,
    FXN_DTYPE_BOOL      = 15,
    FXN_DTYPE_STRING    = 7,
    FXN_DTYPE_LIST      = 8,
    FXN_DTYPE_DICT      = 9,
    FXN_DTYPE_IMAGE     = 16,
    FXN_DTYPE_BINARY    = 17,
};
typedef enum FXNDtype FXNDtype;
#pragma endregion


#pragma region --Types--
/*!
 @struct FXNFeatureType
 
 @abstract Descriptor for an ML feature.

 @discussion Descriptor for an ML feature.
*/
struct FXNFeatureType;
typedef struct FXNFeatureType FXNFeatureType;
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNCreateFeatureType

 @abstract Create a feature type.

 @discussion Create a feature type.

 @param name
 Feature type name.

 @param dtype
 Feature data type.

 @param dims
 Feature dimensions.
 Use `0` for scalar features and `-1` for unknown or undefined dims.

 @param shape
 Feature shape.
 This must contain at least `dims` integers when specified.
 This can be `NULL` for feature types that do not describe tensors.

 @param type
 Created feature type.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNCreateFeatureType (
    const char* name,
    FXNDtype dtype,
    int32_t dims,
    int32_t* shape,
    FXNFeatureType** type
);

/*!
 @function FXNReleaseFeatureType

 @abstract Release a feature type.

 @discussion Release a feature type.

 @param type
 Feature type.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNReleaseFeatureType (FXNFeatureType* type);
#pragma endregion


#pragma region --Operations--
/*!
 @function FXNFeatureTypeName

 @abstract Get the name of a given feature type.

 @discussion Get the name of a given feature type.

 @param type
 Feature type.

 @param name
 Destination UTF-8 string.

 @param size
 Size of destination buffer in bytes.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNFeatureTypeGetName (
    FXNFeatureType* type,
    char* name,
    int32_t size
);

/*!
 @function FXNFeatureTypeGetDtype

 @abstract Get the data type of a given feature type.

 @discussion Get the data type of a given feature type.

 @param type
 Feature type.
*/
FXN_BRIDGE FXN_EXPORT FXNDtype FXN_API FXNFeatureTypeGetDtype (FXNFeatureType* type);

/*!
 @function FXNFeatureTypeGetDimensions

 @abstract Get the number of dimensions for a given feature type.

 @discussion Get the number of dimensions for a given feature type.
 If the type is not a tensor, this function will return `0`.

 @param type
 Feature type.
*/
FXN_BRIDGE FXN_EXPORT int32_t FXN_API FXNFeatureTypeGetDimensions (FXNFeatureType* type);

/*!
 @function FXNFeatureTypeGetShape

 @abstract Get the shape of a given feature type.

 @discussion Get the shape of a given feature type.
 The length of the shape array must be at least as large as the number of dimensions present in the type.

 @param type
 Feature type.

 @param shape
 Destination shape array.
*/
FXN_BRIDGE FXN_EXPORT void FXN_API FXNFeatureTypeGetShape (
    FXNFeatureType* type,
    int32_t* shape
);
#pragma endregion