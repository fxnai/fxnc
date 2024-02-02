//
//  Configuration.hpp
//  Function
//
//  Created by Yusuf Olokoba on 1/30/2024.
//  Copyright © 2024 NatML Inc. All rights reserved.
//

#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <Function/Function.h>

namespace Function {

    class Configuration final {
    public:
        Configuration ();

        explicit Configuration (FXNConfiguration* value, bool owner = true);

        Configuration (const Configuration&) = delete;

        Configuration (Configuration&& other) noexcept;

        ~Configuration ();

        Configuration& operator= (const Configuration&) = delete;

        Configuration& operator= (Configuration&& other) noexcept;

        std::string GetToken () const;

        void SetToken (const std::string& token) const;

        std::filesystem::path GetResource (const std::string& id) const;

        void SetResource (const std::string& id, const std::filesystem::path& path) const;

        FXNAcceleration GetAcceleration () const;

        void SetAcceleration (FXNAcceleration acceleration) const;

        template<typename T>
        T* GetDevice () const;

        template<typename T>
        void SetDevice (T* device) const;

        operator FXNConfiguration* () const;

        static std::string GetUniqueID ();

    private:
        FXNConfiguration* configuration;
        bool owner;
    };
}