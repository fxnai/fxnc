## 0.0.4
+ Added `FXNConfigurationAddResource` function.
+ Updated C API to use `__cdecl` calling convention instead of `__stdcall` on Windows, matching other platforms.
+ Removed `FXNConfigurationGetResource` function.
+ Removed `FXNConfigurationSetResource` function.
+ Removed `FXNValueMapContainsKey` function. Use `FXNValueMapGetValue` function instead.

## 0.0.3
+ Added `FXNValueMapContainsKey` to check whether a given key is present in a value map.

## 0.0.2
+ Added `FXNProfile.h` header for prediction profiling.

## 0.0.1
+ First pre-release.