// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/**
 * @file
 * @brief Provides version information.
 */

#pragma once

#include "azure/core/dll_import_export.hpp"

#include <string>

#define AZURE_CORE_VERSION_MAJOR 1
#define AZURE_CORE_VERSION_MINOR 0
#define AZURE_CORE_VERSION_PATCH 0
#define AZURE_CORE_VERSION_PRERELEASE "beta.9"

namespace Azure { namespace Core { namespace _detail {

  /**
   * @brief Provides version information.
   */
  class PackageVersion {
  public:
    /// Major numeric identifier.
    static constexpr int Major = AZURE_CORE_VERSION_MAJOR;

    /// Minor numeric identifier.
    static constexpr int Minor = AZURE_CORE_VERSION_MINOR;

    /// Patch numeric identifier.
    static constexpr int Patch = AZURE_CORE_VERSION_PATCH;

    /// Optional pre-release identifier. SDK is in a pre-release state when not empty.
    AZ_CORE_DLLEXPORT static std::string const PreRelease;

    /**
     * @brief The version in string format used for telemetry following the `semver.org` standard
     * (https://semver.org).
     */
    static std::string ToString();

  private:
    // To avoid leaking out the #define values we smuggle out the value
    // which will later be used to initialize the PreRelease std::string
    static constexpr const char* secret = AZURE_CORE_VERSION_PRERELEASE;
  };

}}} // namespace Azure::Core::_detail

#undef AZURE_CORE_VERSION_MAJOR
#undef AZURE_CORE_VERSION_MINOR
#undef AZURE_CORE_VERSION_PATCH
#undef AZURE_CORE_VERSION_PRERELEASE
