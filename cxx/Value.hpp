//
//  Value.hpp
//  Function
//
//  Created by Yusuf Olokoba on 1/30/2024.
//  Copyright © 2024 NatML Inc. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <Function/Function.h>

namespace Function {

    class Value final {
    public:
        explicit Value (FXNValue* value, bool owner = true);

        Value (const Value&) = delete;

        Value (Value&& other) noexcept;

        ~Value ();

        Value& operator= (const Value&) = delete;

        Value& operator= (Value&& other) noexcept;

        void* GetData () const;

        template<typename T>
        T* GetData () const;

        FXNDtype GetType () const;

        int32_t GetDimensions () const;

        std::vector<int32_t> GetShape () const;

        operator FXNValue* () const;

        template<typename T>
        static Value CreateArray (T* data, const std::vector<int32_t>& shape, FXNValueFlags flags);

        static Value CreateString (const std::string& str);

        static Value CreateList (const std::string& jsonList);

        static Value CreateDict (const std::string& jsonDict);

        static Value CreateImage (const uint8_t* pixelBuffer, int32_t width, int32_t height, int32_t channels, FXNValueFlags flags);

        static Value CreateBinary (void* buffer, int64_t bufferLen, FXNValueFlags flags);
        
        static Value CreateNull ();
    private:
        FXNValue* value;
        bool owner;
    };
}