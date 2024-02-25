cmake_minimum_required(VERSION 3.20)

# Get version
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/include/Function/FXNVersion.h" FXN_VERSION_HEADER_CONTENTS)
string(REGEX MATCH "FXN_VERSION_MAJOR ([0-9]+)" FXN_VERSION_MAJOR_MATCH ${FXN_VERSION_HEADER_CONTENTS})
string(REGEX MATCH "FXN_VERSION_MINOR ([0-9]+)" FXN_VERSION_MINOR_MATCH ${FXN_VERSION_HEADER_CONTENTS})
string(REGEX MATCH "FXN_VERSION_PATCH ([0-9]+)" FXN_VERSION_PATCH_MATCH ${FXN_VERSION_HEADER_CONTENTS})
string(REGEX REPLACE "FXN_VERSION_MAJOR ([0-9]+)" "\\1" FXN_VERSION_MAJOR ${FXN_VERSION_MAJOR_MATCH})
string(REGEX REPLACE "FXN_VERSION_MINOR ([0-9]+)" "\\1" FXN_VERSION_MINOR ${FXN_VERSION_MINOR_MATCH})
string(REGEX REPLACE "FXN_VERSION_PATCH ([0-9]+)" "\\1" FXN_VERSION_PATCH ${FXN_VERSION_PATCH_MATCH})
set(FXN_VERSION "${FXN_VERSION_MAJOR}.${FXN_VERSION_MINOR}.${FXN_VERSION_PATCH}")
message(STATUS "Function ${FXN_VERSION}")

# Define project
project(
    Function
    VERSION ${FXN_VERSION}
    DESCRIPTION "Function unified C/C++ API for running Python functions on desktop, mobile, web, and in the cloud. Register at https://fxn.ai"
    HOMEPAGE_URL "https://github.com/fxnai/fxnc"
    LANGUAGES C CXX
)

# Settings
set(FXN_PLATFORM "FXN_PLATFORM_AUTO" CACHE STRING "Specify the target Function platform and architecture")
set_property(CACHE FXN_PLATFORM PROPERTY STRINGS
    "FXN_PLATFORM_AUTO"
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

# Infer platform
if(FXN_PLATFORM STREQUAL "FXN_PLATFORM_AUTO")
    if(CMAKE_SYSTEM_NAME STREQUAL "Android")
        if (ANDROID_ABI STREQUAL "armeabi-v7a")
            set(FXN_PLATFORM "FXN_PLATFORM_ANDROID_ARM")
        elseif(ANDROID_ABI STREQUAL "arm64-v8a")
            set(FXN_PLATFORM "FXN_PLATFORM_ANDROID_ARM64")
        elseif(ANDROID_ABI STREQUAL "x86")
            set(FXN_PLATFORM "FXN_PLATFORM_ANDROID_X86")
        elseif(ANDROID_ABI STREQUAL "x86_64")
            set(FXN_PLATFORM "FXN_PLATFORM_ANDROID_X64")
        else()
            message(FATAL_ERROR "Failed to infer Function platform because of unsupported Android ABI: ${ANDROID_ABI}")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        if(CMAKE_OSX_ARCHITECTURES)
            # Check CMAKE_OSX_ARCHITECTURES in case we're cross-compiling
            list(GET CMAKE_OSX_ARCHITECTURES 0 osx_arch)
            if(osx_arch STREQUAL "x86_64")
                set(FXN_PLATFORM "FXN_PLATFORM_MACOS_X64")
            elseif(osx_arch STREQUAL "arm64")
                set(FXN_PLATFORM "FXN_PLATFORM_MACOS_ARM64")
            else()
                message(FATAL_ERROR "Failed to infer Function platform because of unsupported architecture: ${osx_arch}")
            endif()
        else()
            # Infer from host architecture
            if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
                set(FXN_PLATFORM "FXN_PLATFORM_MACOS_X64")
            elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
                set(FXN_PLATFORM "FXN_PLATFORM_MACOS_X64")
            else()
                message(FATAL_ERROR "Failed to infer Function platform because of unsupported host architecture: ${CMAKE_SYSTEM_PROCESSOR}")
            endif()
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
        set(FXN_PLATFORM "FXN_PLATFORM_WASM")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        if(CMAKE_GENERATOR_PLATFORM MATCHES "x64")
            set(FXN_PLATFORM "FXN_PLATFORM_WINDOWS_X64")
        else()
            message(FATAL_ERROR "Failed to infer Function platform because of unsupported architecture: ${CMAKE_GENERATOR_PLATFORM}")
        endif()
    else()
        message(FATAL_ERROR "Failed to infer Function platform because on unsupported system: ${CMAKE_SYSTEM_NAME}")
    endif()
endif()

# Download Function
function(generate_download_url)
    if(FXN_PLATFORM STREQUAL "FXN_PLATFORM_ANDROID_ARM")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-android-armeabi-v7a.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_ANDROID_ARM64")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-android-arm64-v8a.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_ANDROID_X86")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-android-x86.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_ANDROID_X64")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-android-x86_64.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_IOS_ARM64")
        # set(FXN_LIB_NAME "libFunction.a" PARENT_SCOPE)
        # set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-ios-arm64.a" PARENT_SCOPE)
        message(FATAL_ERROR "Function support for iOS has not yet been launched")
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_MACOS_ARM64")
        set(FXN_LIB_NAME "Function.dylib" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/Function-macos-arm64.dylib" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_MACOS_X64")
        set(FXN_LIB_NAME "Function.dylib" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/Function-macos-x86_64.dylib" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_WASM")
        set(FXN_LIB_NAME "libFunction.so" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/libFunction-wasm.so" PARENT_SCOPE)
    elseif(FXN_PLATFORM STREQUAL "FXN_PLATFORM_WINDOWS_X64")
        set(FXN_LIB_NAME "Function.dll" PARENT_SCOPE)
        set(FXN_IMPLIB_NAME "Function.lib" PARENT_SCOPE)
        set(FXN_LIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/Function-win64.dll" PARENT_SCOPE)
        set(FXN_IMPLIB_URL "https://cdn.fxn.ai/edgefxn/${FXN_VERSION}/Function-win64.lib" PARENT_SCOPE)
    else()
        message(FATAL_ERROR "Failed to download Function library due to invalid platform: ${FXN_PLATFORM}")
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

# Download library
file(MAKE_DIRECTORY ${FXN_LIB_DIR})
message(STATUS "Downloading ${FXN_LIB_NAME} from ${FXN_LIB_URL}")
file(DOWNLOAD
    ${FXN_LIB_URL} ${FXN_LIB_PATH}
    TLS_VERIFY ON
    TIMEOUT 60
    STATUS fxn_download_status
    LOG fxn_download_log
)
list(GET fxn_download_status 0 fxn_download_status_code)
list(GET fxn_download_status 1 fxn_download_error_message)
if(NOT ${fxn_download_status_code} STREQUAL "0")
    message(FATAL_ERROR "Function library download failed: ${fxn_download_error_message}\nLog: ${fxn_download_log}")
endif()

# Download the import library for Windows
if (DEFINED FXN_IMPLIB_URL)
    message(STATUS "Downloading ${FXN_IMPLIB_NAME} from ${FXN_IMPLIB_URL}")
    file(DOWNLOAD
        ${FXN_IMPLIB_URL} ${FXN_IMPLIB_PATH}
        TLS_VERIFY ON
        TIMEOUT 60
        STATUS fxn_implib_download_status
        LOG fxn_implib_download_log
    )
    list(GET fxn_download_status 0 fxn_implib_download_status_code)
    list(GET fxn_download_status 1 fxn_implib_download_error_message)
    if(NOT ${fxn_implib_download_status_code} STREQUAL "0")
        message(FATAL_ERROR "Function implementation library download failed: ${fxn_implib_download_error_message}\nLog: ${fxn_implib_download_log}")
    endif()
endif()

# Define target
add_library(Function::Function SHARED IMPORTED GLOBAL)
target_compile_features(Function::Function INTERFACE cxx_std_17)
target_include_directories(Function::Function INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(Function::Function PROPERTIES IMPORTED_LOCATION ${FXN_LIB_PATH})
if(DEFINED FXN_IMPLIB_PATH)
    set_target_properties(Function::Function PROPERTIES IMPORTED_IMPLIB ${FXN_IMPLIB_PATH})
endif()