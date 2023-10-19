//
//  FXNValue.h
//  Function
//
//  Created by Yusuf Olokoba on 5/27/2023.
//  Copyright © 2023 NatML Inc. All rights reserved.
//

#pragma once

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

/*!
 @enum FXNValueFlags

 @abstract Value flags.

 @constant FXN_VALUE_FLAG_NONE
 No flags.

 @constant FXN_VALUE_FLAG_COPY_DATA
 Copy input data when creating a value.
 When this flag is not set, the value data MUST remain valid for the lifetime of the created value.
*/
enum FXNValueFlags {
    FXN_VALUE_FLAG_NONE         = 0,
    FXN_VALUE_FLAG_COPY_DATA    = 1,
};
typedef enum FXNValueFlags FXNValueFlags;
#pragma endregion


#pragma region --Types--
/*!
 @struct FXNValue
 
 @abstract Predictor input or output value.

 @discussionPredictor input or output value.
 This is loosely based on `DLPack::DLTensor`.
*/
struct FXNValue;
typedef struct FXNValue FXNValue;
#pragma endregion


#pragma region --Lifecycle--
/*!
 @function FXNValueRelease

 @abstract Release a value.

 @discussion Release a value.

 @param value
 Value.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueRelease (FXNValue* value);
#pragma endregion


#pragma region --Operations--
/*!
 @function FXNValueGetData

 @abstract Get the value data.

 @discussion Get the value data.

 @param value
 Value.

 @param data
 Opaque pointer to value data.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueGetData (
    FXNValue* value,
    void** data
);

/*!
 @function FXNValueGetType

 @abstract Get the data type of a given value.

 @discussion Get the data type of a given valuie.

 @param value
 Value.

 @param type
 Value data type.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueGetType (
    FXNValue* value,
    FXNDtype* type
);

/*!
 @function FXNValueGetDimensions

 @abstract Get the number of dimensions for a given value.

 @discussion Get the number of dimensions for a given value.
 If the type is not a tensor, this function will return zero.

 @param value
 Value.

 @param dimensions
 Number of dimensions for a given value.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueGetDimensions (
    FXNValue* value,
    int32_t* dimensions
);

/*!
 @function FXNValueGetShape

 @abstract Get the shape of a given value.

 @discussion Get the shape of a given value.

 @param value
 Value.

 @param shape
 Destination shape array.

 @param shapeLen
 Length of the destination array.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueGetShape (
    FXNValue* value,
    int32_t* shape,
    int32_t shapeLen
);
#pragma endregion


#pragma region --Constructors--
/*!
 @function FXNValueCreateArray

 @abstract Create an array value from a data buffer.

 @discussion Create an array value from a data buffer.

 @param data
 Array data.

 @param shape
 Array shape.
 Can be `NULL` for scalar values.

 @param dims
 Number of dimensions in `shape`.
 Zero dims indicates a scalar value.

 @param dtype
 Value data type.

 @param flags
 Value creation flags.

 @param value
 Created value.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueCreateArray (
    void* data,
    const int32_t* shape,
    int32_t dims,
    FXNDtype dtype,
    FXNValueFlags flags,
    FXNValue** value
);

/*!
 @function FXNValueCreateString

 @abstract Create a string value from a UTF-8 encoded string.
 
 @discussion Create a string value from a UTF-8 encoded string.

 @param data
 UTF-8 encoded string.

 @param value
 Created value.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueCreateString (
    const char* data,
    FXNValue** value
);

/*!
 @function FXNValueCreateList

 @abstract Create a list value from a JSON-encoded list.
 
 @discussion Create a list value from a JSON-encoded list.

 @param data
 JSON-encoded list.

 @param value
 Created value.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueCreateList (
    const char* data,
    FXNValue** value
);

/*!
 @function FXNValueCreateDict

 @abstract Create a dictionary value from a JSON-encoded dictionary.
 
 @discussion Create a dictionary value from a JSON-encoded dictionary.

 @param data
 JSON-encoded dictionary.

 @param value
 Created value.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueCreateDict (
    const char* data,
    FXNValue** value
);

/*!
 @function FXNValueCreateImage

 @abstract Create an image value from a pixel buffer.

 @discussion Create an image value from a pixel buffer.
 The pixel buffer MUST have an interleaved RGBA8888 layout (32 bits per pixel).

 @param pixelBuffer
 Pixel buffer.

 @param width
 Pixel buffer width.

 @param height
 Pixel buffer height.

 @param flags
 Value creation flags.

 @param value
 Created value.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueCreateImage (
    const uint8_t* pixelBuffer,
    int32_t width,
    int32_t height,
    FXNValueFlags flags,
    FXNValue** value
);

/*!
 @function FXNValueCreateBinary

 @abstract Create a binary value from a raw buffer.
 
 @discussion Create a binary value from a raw buffer.

 @param buffer
 Buffer.

 @param bufferLen
 Buffer length in bytes.

 @param flags
 Value creation flags.

 @param value
 Created value.
*/
FXN_BRIDGE FXN_EXPORT FXNStatus FXN_API FXNValueCreateBinary (
    void* buffer,
    int64_t bufferLen,
    FXNValueFlags flags,
    FXNValue** value
);
#pragma endregion