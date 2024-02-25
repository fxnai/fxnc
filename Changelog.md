## 0.0.6
+ Fixed C++ double-free error when retrieving a `Function::Value` from a `Function::ValueMap`.

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
+ Added Function C API implementations for Android, iOS, macOS, and WebAssembly.
+ Added `FXNConfigurationGetResource` function for retrieving a configuration resource.
+ Added `FXNConfigurationSetResource` function for specifying a configuration resource.
+ Added `FXNProfile.h` header for prediction profiling.

## 0.0.1
+ First pre-release.