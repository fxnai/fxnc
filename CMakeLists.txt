cmake_minimum_required(VERSION 3.20)
project(Function)

# Settings
set(FXN_VERSION "0.0.3")
set(FXN_PLATFORM "" CACHE STRING "Specify the target Function platform and architecture")
set_property(CACHE FXN_PLATFORM PROPERTY STRINGS
    "FXN_PLATFORM_ANDROID_ARM"
    "FXN_PLATFORM_ANDROID_ARM64"
    "FXN_PLATFORM_ANDROID_X86"
    "FXN_PLATFORM_ANDROID_X64"
    "FXN_PLATFORM_IOS_ARM64"
    "FXN_PLATFORM_MACOS_X64"
    "FXN_PLATFORM_MACOS_ARM64"
    "FXN_PLATFORM_LINUX_X64"
    "FXN_PLATFORM_LINUX_ARM64"
    "FXN_PLATFORM_WASM"
    "FXN_PLATFORM_WINDOWS_X64"
)

# Check platform
if(FXN_PLATFORM STREQUAL "")
    message(FATAL_ERROR "Please specify a platform by setting FXN_PLATFORM.")
endif()

# Download Function
function(generate_download_url)
    if(FXN_PLATFORM STREQUAL "FXN_PLATFORM_ANDROID_ARM")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-android-arm.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_ANDROID_ARM64")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-android-arm64.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_ANDROID_X86")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-android-x86.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_ANDROID_X64")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-android-x64.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_IOS_ARM64")
        set(FXN_LIB_NAME "libFunction.a" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-ios-arm64.a" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_MACOS_X64" OR FXN_PLATFORM STREQUAL "FXN_PLATFORM_MACOS_ARM64")
        set(FXN_LIB_NAME "Function.dylib" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/Function-macos.dylib" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_WINDOWS_X64")
        set(FXN_LIB_NAME "Function.dll" PARENT_SCOPE)
        set(FXN_IMPLIB_NAME "Function.lib" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/Function-win64.dll" PARENT_SCOPE)
        set(FXN_IMPLIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/Function-win64.lib" PARENT_SCOPE)
    endif()
endfunction()

# Populate URLs
generate_download_url()

# Resolve paths
set(FXN_LIB_DIR "${CMAKE_BINARY_DIR}/Function")
set(FXN_LIB_PATH "${FXN_LIB_DIR}/${FXN_LIB_NAME}")
if (DEFINED FXN_IMPLIB_NAME)
    set(FXN_IMPLIB_PATH "${FXN_LIB_DIR}/${FXN_IMPLIB_NAME}")
endif()

# Create the directory and download the library
file(MAKE_DIRECTORY ${FXN_LIB_DIR})
message(STATUS "Downloading ${FXN_LIB_NAME} from ${FXN_LIB_URL}")
file(DOWNLOAD
    ${FXN_LIB_URL} ${FXN_LIB_PATH}
    TLS_VERIFY ON
    TIMEOUT 60
    LOG fxn_download_log
)

# Download the import library for Windows, if applicable
if (DEFINED FXN_IMPLIB_URL)
    message(STATUS "Downloading ${FXN_IMPLIB_NAME} from ${FXN_IMPLIB_URL}")
    file(DOWNLOAD
        ${FXN_IMPLIB_URL} ${FXN_IMPLIB_PATH}
        TLS_VERIFY ON
        TIMEOUT 60
        LOG fxn_implib_download_log
    )
endif()

# Define target
add_library(Function::Function SHARED IMPORTED GLOBAL)
target_compile_features(Function::Function INTERFACE cxx_std_17)
target_include_directories(Function::Function INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(Function::Function PROPERTIES IMPORTED_LOCATION ${FXN_LIB_PATH})
if(DEFINED FXN_IMPLIB_PATH)
    set_target_properties(Function::Function PROPERTIES IMPORTED_IMPLIB ${FXN_IMPLIB_PATH})
endif()

message(STATUS ${FXN_LIB_PATH})