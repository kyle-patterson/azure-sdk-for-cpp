// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/**
 * @brief Define the base classes for using single page responses.
 *
 */

#pragma once

#include <azure/core/nullable.hpp>

#include <string>

namespace Azure { namespace Security { namespace KeyVault { namespace _internal {
  struct SinglePage
  {
    Azure::Nullable<std::string> ContinuationToken;
  };

  struct GetSinglePageOptions
  {
    Azure::Nullable<std::string> ContinuationToken;
    Azure::Nullable<uint32_t> MaxPageResults;
  };
}}}} // namespace Azure::Security::KeyVault::_internal
