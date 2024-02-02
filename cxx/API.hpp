//
//  API.hpp
//  Function
//
//  Created by Yusuf Olokoba on 1/30/2024.
//  Copyright © 2024 NatML Inc. All rights reserved.
//

#pragma once

#include <vector>
#include "Assert.hpp"
#include "Configuration.hpp"
#include "Value.hpp"

namespace Function {

#pragma region --Configuration--

inline Configuration::Configuration () {
    FXNConfigurationCreate(&configuration);
    owner = true;
}

inline Configuration::Configuration (FXNConfiguration* value, bool owner) : configuration(value), owner(owner) {

}

inline Configuration::Configuration(Configuration&& other) noexcept : configuration(other.configuration), owner(other.owner) {
    other.configuration = nullptr;
    other.owner = false;
}

inline Configuration::~Configuration () {
    if (owner)
        FXNConfigurationRelease(configuration);
}

inline Configuration& Configuration::operator= (Configuration&& other) noexcept {
    // Check
    if (this == &other)
        return *this;
    // Move
    if (owner)
        FXNConfigurationRelease(configuration);
    configuration = other.configuration;
    owner = other.owner;
    other.configuration = nullptr;
    other.owner = false;
    // Return
    return *this;
}

inline std::string Configuration::GetToken () const {
    std::string token;
    token.resize(4096);
    FXNConfigurationGetToken(configuration, token.data(), static_cast<int>(token.size()));
    token.resize(strlen(token.c_str()));
    return token;
}

inline void Configuration::SetToken (const std::string& token) const {
    FXNConfigurationSetToken(configuration, token.c_str());
}

inline std::filesystem::path Configuration::GetResource (const std::string& id) const {
    std::string path;
    path.resize(4096);
    FXNConfigurationGetResource(configuration, id.c_str(), path.c_str(), static_cast<int>(path.size()));
    path.resize(strlen(path.c_str()));
    return std::filesystem::path(path);
}

inline void Configuration::SetResource (const std::string& id, const std::filesystem::path& path) const {
    FXNConfigurationSetResource(configuration, id.c_str(), path.c_str());
}

inline FXNAcceleration Configuration::GetAcceleration () const {
    FXNAcceleration acceleration;
    FXNConfigurationGetAcceleration(configuration, &acceleration);
    return acceleration;
}

inline void Configuration::SetAcceleration (FXNAcceleration acceleration) const {
    FXNConfigurationSetAcceleration(configuration, acceleration);
}

template<typename T>
inline T* Configuration::GetDevice () const {
    void* device = nullptr;
    FXNConfigurationGetDevice(configuration, &device);
    return static_cast<T*>(device);
}

template<typename T>
inline T* Configuration::SetDevice (T* device) const {
    FXNConfigurationSetDevice(configuration, device);
}

inline Configuration::operator FXNConfiguration* () const {
    return configuration;
}

inline std::string Configuration::GetUniqueID () {
    std::string id;
    id.resize(1024);
    FXNConfigurationGetUniqueID(id.data(), static_cast<int>(id.size()));
    id.resize(strlen(id.c_str()));
    return id;
}
#pragma endregion


#pragma region --Value--

template <typename T>
struct ToFXNDtype;
template <>
struct ToFXNDtype<float> {
    static constexpr FXNDtype type = FXN_DTYPE_FLOAT32;
};
template <>
struct ToFXNDtype<double> {
    static constexpr FXNDtype type = FXN_DTYPE_FLOAT64;
};
template <>
struct ToFXNDtype<int8_t> {
    static constexpr FXNDtype type = FXN_DTYPE_INT8;
};
template <>
struct ToFXNDtype<int16_t> {
    static constexpr FXNDtype type = FXN_DTYPE_INT16;
};
template <>
struct ToFXNDtype<int32_t> {
    static constexpr FXNDtype type = FXN_DTYPE_INT32;
};
template <>
struct ToFXNDtype<int64_t> {
    static constexpr FXNDtype type = FXN_DTYPE_INT64;
};
template <>
struct ToFXNDtype<uint8_t> {
    static constexpr FXNDtype type = FXN_DTYPE_UINT8;
};
template <>
struct ToFXNDtype<uint16_t> {
    static constexpr FXNDtype type = FXN_DTYPE_UINT16;
};
template <>
struct ToFXNDtype<uint32_t> {
    static constexpr FXNDtype type = FXN_DTYPE_UINT32;
};
template <>
struct ToFXNDtype<uint64_t> {
    static constexpr FXNDtype type = FXN_DTYPE_UINT64;
};
template <>
struct ToFXNDtype<bool> {
    static constexpr FXNDtype type = FXN_DTYPE_BOOL;
};

inline Value::Value (FXNValue* value, bool owner) : value(value), owner(owner) {

}

inline Value::Value (Value&& other) noexcept : value(other.value) {
    other.value = nullptr;
}

inline Value::~Value () {
    if (owner)
        FXNValueRelease(value);
}

inline Value& Value::operator= (Value&& other) noexcept {
    // Check
    if (this == &other)
        return *this;
    // Move
    if (owner)
        FXNValueRelease(value);
    value = other.value;
    owner = other.owner;
    other.value = nullptr;
    other.owner = false;
    // Return
    return *this;
}

inline void* Value::GetData () const {
    void* data;
    FXNValueGetData(value, &data);
    return data;
}

template<typename T>
inline T* Value::GetData () const {
    return static_cast<T*>(GetData());
}

inline FXNDtype Value::GetType () const {
    FXNDtype type;
    FXNValueGetType(value, &type);
    return type;
}

inline int32_t Value::GetDimensions () const {
    int32_t dimensions;
    FXNValueGetDimensions(value, &dimensions);
    return dimensions;
}

inline std::vector<int32_t>  Value::GetShape () const {
    int32_t dimensions = GetDimensions();
    std::vector<int32_t> shape(dimensions);
    FXNValueGetShape(value, shape.data(), dimensions);
    return shape;
}

inline Value::operator FXNValue* () const {
    return value;
}

template<typename T>
inline Value Value::CreateArray (T* data, const std::vector<int32_t>& shape, FXNValueFlags flags) {
    FXNValue* fxnValue;
    FXNValueCreateArray(data, shape.data(), static_cast<int32_t>(shape.size()), ToFXNDtype<T>::type, flags, &fxnValue);
    return Value(fxnValue);
}

inline Value Value::CreateString (const std::string& str) {
    FXNValue* fxnValue;
    FXNValueCreateString(str.c_str(), &fxnValue);
    return Value(fxnValue);
}

inline Value Value::CreateList (const std::string& jsonList) {
    FXNValue* fxnValue;
    FXNValueCreateList(jsonList.c_str(), &fxnValue);
    return Value(fxnValue);
}

inline Value Value::CreateDict (const std::string& jsonDict) {
    FXNValue* fxnValue;
    FXNValueCreateDict(jsonDict.c_str(), &fxnValue);
    return Value(fxnValue);
}

inline Value Value::CreateImage (const uint8_t* pixelBuffer, int32_t width, int32_t height, int32_t channels, FXNValueFlags flags) {
    FXNValue* fxnValue;
    FXNValueCreateImage(pixelBuffer, width, height, channels, flags, &fxnValue);
    return Value(fxnValue);
}

inline Value Value::CreateBinary (void* buffer, int64_t bufferLen, FXNValueFlags flags) {
    FXNValue* fxnValue;
    FXNValueCreateBinary(buffer, bufferLen, flags, &fxnValue);
    return Value(fxnValue);
}

inline Value Value::CreateNull () {
    FXNValue* fxnValue;
    FXNValueCreateNull(&fxnValue);
    return Value(fxnValue);
}
#pragma endregion

}