//
//  Dialect.hpp
//  Function
//
//  Created by Yusuf Olokoba on 1/25/2024.
//  Copyright © 2024 NatML Inc. All rights reserved.
//

#pragma once

/**
 @abstract Function dialect definition.
 
 @discussion This header provides enables developers to bring their custom operators to the Function platform.
 
 NOTE: This header is EXPERIMENTAL.
*/

#pragma region --Platform--
/*!
 @enum FXNPlatform

 @abstract Current platform.

 @constant FXN_PLATFORM_UNKNOWN
 Unknown platform.

 @constant FXN_PLATFORM_ANDROID_ARM
 Android armeabi-v7a platform.

 @constant FXN_PLATFORM_ANDROID_ARM64
 Android arm64-v8a platform.

 @constant FXN_PLATFORM_ANDROID_X86
 Android x86 platform.

 @constant FXN_PLATFORM_ANDROID_X64
 Android x86_64 platform.

 @constant FXN_PLATFORM_ANDROID
 Android platform across all ABIs.

 @constant FXN_PLATFORM_IOS
 iOS platform.
 
 @constant FXN_PLATFORM_MACOS_X64
 macOS x86_64 platform.

 @constant FXN_PLATFORM_MACOS_ARM64
 macOS arm64 platform.

 @constant FXN_PLATFORM_MACOS
 macOS platform across all ABIs.

 @constant FXN_PLATFORM_LINUX_X64
 Linux x86_64 platform.

 @constant FXN_PLATFORM_LINUX_ARM64
 Linux arm64 platform.

 @constant FXN_PLATFORM_LINUX
 Linux platform across all ABIs.

 @constant FXN_PLATFORM_WASM
 WebAssembly platform.

 @constant FXN_PLATFORM_WINDOWS_X64
 Windows x86_64 platform.

 @constant FXN_PLATFORM_WINDOWS
 Windows platform across all ABIs.
*/
enum FXNPlatform {
    FXN_PLATFORM_UNKNOWN        = 0,
    FXN_PLATFORM_ANDROID_ARM    = 1 << 0,
    FXN_PLATFORM_ANDROID_ARM64  = 1 << 1,
    FXN_PLATFORM_ANDROID_X86    = 1 << 2,
    FXN_PLATFORM_ANDROID_X64    = 1 << 3,
    FXN_PLATFORM_ANDROID        = FXN_PLATFORM_ANDROID_ARM | FXN_PLATFORM_ANDROID_ARM64 | FXN_PLATFORM_ANDROID_X86 | FXN_PLATFORM_ANDROID_X64,
    FXN_PLATFORM_IOS            = 1 << 4,
    FXN_PLATFORM_MACOS_X64      = 1 << 5,
    FXN_PLATFORM_MACOS_ARM64    = 1 << 6,
    FXN_PLATFORM_MACOS          = FXN_PLATFORM_MACOS_X64 | FXN_PLATFORM_MACOS_ARM64,
    FXN_PLATFORM_LINUX_X64      = 1 << 7,
    FXN_PLATFORM_LINUX_ARM64    = 1 << 8,
    FXN_PLATFORM_LINUX          = FXN_PLATFORM_LINUX_X64 | FXN_PLATFORM_LINUX_ARM64,
    FXN_PLATFORM_WASM           = 1 << 9,
    FXN_PLATFORM_WINDOWS_X64    = 1 << 10,
    FXN_PLATFORM_WINDOWS        = FXN_PLATFORM_WINDOWS_X64,
};
typedef enum FXNPlatform FXNPlatform;

/*!
 @enum FXNInferenceFormat

 @abstract Model format used by inference operators.

 @discussion Inference operators can define their desired neural network format.
 EdgeFunction will attempt to convert any models encountered during tracing into this format.
 
 @constant FXN_INFERENCE_FORMAT_UNKNOWN
 Unknown or unsupported inference format.

 @constant FXN_INFERENCE_FORMAT_FXN
 Function built-in inference format.

 @constant FXN_INFERENCE_FORMAT_ONNX
 ONNX inference format.

 @constant FXN_INFERENCE_FORMAT_COREML
 Apple CoreML inference format.

 @constant FXN_INFERENCE_FORMAT_GGML
 GGML inference format for quantized large language model (LLM) inference.
*/
enum FXNInferenceFormat {
    FXN_INFERENCE_FORMAT_UNKNOWN    = 0,
    FXN_INFERENCE_FORMAT_FXN        = 1,
    FXN_INFERENCE_FORMAT_ONNX       = 2,
    FXN_INFERENCE_FORMAT_COREML     = 3,
    FXN_INFERENCE_FORMAT_GGML       = 4,
};
typedef enum FXNInferenceFormat FXNInferenceFormat;
#pragma endregion


#pragma region --Operators--
/*!
 @abstract Function operator.

 @discussion The enclosing class or struct defines a function operator.

 @param opname
 Python operator name that this definition applies to.
*/
#define FXN_FUNCTION_OP(opname)

/*!
 @abstract Cast operator.

 @discussion The enclosing class or struct defines a value cast operator.
*/
#define FXN_CAST_OP(...)

/*!
 @abstract Neural network inference operator.

 @discussion The enclosing class or struct defines a neural network inference operator.

 @param format
 Neural network format that should be provided to the operator.

 @see FXNInferenceFormat
*/
#define FXN_INFERENCE_OP(format)
#pragma endregion


#pragma region --Operator Properties--
/*!
 @abstract Operator desscription.

 @discussion The description is useful for providing analytics and diagnostic information.

 @param description
 Operator description.
*/
#define FXN_OP_DESCRIPTION(description)

/*!
 @abstract Operator supported platforms.

 @discussion Specify which platforms the operator is supported on.

 @param platform
 Supported platforms. Use `|` to specify multiple platforms.
*/
#define FXN_OP_PLATFORM(platform)

/*!
 @abstract Operator library dependency.

 @discussion Specify a library dependency for the operator.

 @param target
 Target to link against when compiling the predictor. This is usually the name of a library or framework.

 @param include
 CMake include definition for defining the `target`. Pass `FXN_LIBRARY_NO_INCLUDE` if there is no include.

 @param platform
 Specify the platform that this library dependency applies to.
*/
#define FXN_OP_LIBRARY(target,include,platform)

/*!
 @abstract Operator metadata.

 @discussion Specify operator metadata as a key-value pair. This is useful in analytics.
 
 @param key
 Metadata key.

 @param value
 Metadata value.
*/
#define FXN_OP_METADATA(key, value)

/*!
 @abstract Operator documentation URL.

 @discussion Specify the operator documentation URL. This is useful in analytics.
 
 @param url
 Operator documentation URL.
*/
#define FXN_OP_DOCS(url)

/*!
 @abstract Operator keyword argument.

 @discussion This is used to bind keyword arguments from Python into a C++ positional argument.
 
 @param name
 Keyword argument name.
*/
#define FXN_OP_KWARG(name)
#pragma endregion


#pragma region --Operator Constants--
#define FXN_LIBRARY_NO_INCLUDE ""
#define FXN_KWARG_MODEL_CONFIGURATION "model_configuration"
#define FXN_MODEL_RESOURCE_KEY "model_resource"
#pragma endregion