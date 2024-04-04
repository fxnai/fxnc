## 0.0.16
+ Fixed crash in `FXNPredictorCreate` when certain predictors cannot be loaded.

## 0.0.15
+ Fixed predictor creation failing on Android.
+ Fixed predictor creation failing sporadically on Windows.
+ Fixed corrupted JSON string in `FXNValueCreateDict` and `FXNValueCreateList` functions.

## 0.0.14
+ Fixed edge predictions failing in the browser when using backend proxy service.

## 0.0.13
+ Minor updates.

## 0.0.12
+ Function is now compiled as a `MAIN_MODULE` on WebAssembly. See `Function.js` and `Function.wasm` release artifacts.

## 0.0.11
+ Added `FXN_PLATFORM_WASM32` platform constant for targeting 32-bit WebAssembly.
+ Added experimental `FXN_PLATFORM_WASM64` platform constant for targeting 64-bit WebAssembly (Memory64).
+ Fixed compiler errors when building for WebAssembly by importing Emscripten headers.
+ Updated `FXN_PLATFORM_WASM` platform constant to contain both `FXN_PLATFORM_WASM32` and `FXN_PLATFORM_WASM64`.

## 0.0.10
+ Refactored `FXN_INFERENCE_FORMAT_GGML` constant to `FXN_INFERENCE_FORMAT_GGUF`.
+ Removed `FXNInferenceFormat` enumeration.

## 0.0.9
+ Added support for loading predictors in sandboxed iOS and macOS apps.

## 0.0.8
+ Fixed predictor creation failing on iOS.

## 0.0.7
+ Added Function C API implementation for iOS.
+ Added codesigning for macOS libraries.

## 0.0.6
+ Added `FXNConfigurationGetTag` function for retrieving the predictor tag from a configuration.
+ Added `FXNConfigurationSetTag` function for setting the predictor tag in a configuration.
+ Added `Function::Configuration::GetTag` method for retrieving the predictor tag from a configuration.
+ Added `Function::Configuration::SetTag` method for setting the predictor tag in a configuration.
+ Added `FXNPredictionGetResults` function for retrieving prediction outputs value map.
+ Added `Function::Prediction` class for working with predictions.
+ Fixed C++ double-free error when retrieving a `Function::Value` from a `Function::ValueMap`.
+ Updated `FXNPredictorCreate` function to no longer accept a `tag`. Specify the tag in the configuration instead.
+ Updated `FXNPredictorPredict` function to accept an `FXNPrediction**` in place of a profile and output value map.
+ Refactored `FXNProfile` struct to `FXNPrediction`.
+ Refactored `FXNProfileGetID` function to `FXNPredictionGetID`.
+ Refactored `FXNProfileGetLatency` function to `FXNPredictionGetLatency`.
+ Refactored `FXNProfileGetError` function to `FXNPredictionGetError`.
+ Refactored `FXNProfileGetLogLength` function to `FXNPredictionGetLogLength`.
+ Refactored `FXNProfileGetLogs` function to `FXNPredictionGetLogs`.
+ Refactored `FXNProfileRelease` function to `FXNPredictionRelease.`

## 0.0.5
+ Added CMake improvements.
+ Fixed linker errors when building for macOS x86_64.

## 0.0.4
+ Added `FXNConfigurationAddResource` function.
+ Updated C API to use `__cdecl` calling convention instead of `__stdcall` on Windows, matching other platforms.
+ Removed `FXNConfigurationGetResource` function.
+ Removed `FXNConfigurationSetResource` function.
+ Removed `FXNValueMapContainsKey` function. Use `FXNValueMapGetValue` function instead.

## 0.0.3
+ Added `FXNValueMapContainsKey` to check whether a given key is present in a value map.
+ Added `FXNProfileGetLogLength` to get the length of the logs in the profile.
+ Added support for setting interleaved `channels` count in `FXNValueCreateImage`.

## 0.0.2
+ Added Function C API implementations for Android, macOS, and WebAssembly.
+ Added `FXNConfigurationGetResource` function for retrieving a configuration resource.
+ Added `FXNConfigurationSetResource` function for specifying a configuration resource.
+ Added `FXNProfile.h` header for prediction profiling.

## 0.0.1
+ First pre-release.