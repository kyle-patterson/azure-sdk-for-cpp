# Copyright (c) Microsoft Corporation. All rights reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required (VERSION 3.13)
project(azure-identity LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake-modules")

include(AzureVcpkg)
include(AzureVersion)
include(AzureCodeCoverage)
include(AzureTransportAdapters)
include(AzureDoxygen)
include(AzureGlobalCompileOptions)

az_vcpkg_integrate()

if(NOT AZ_ALL_LIBRARIES)
  find_package(azure-core-cpp CONFIG QUIET)
  if(NOT azure-core-cpp_FOUND)
    find_package(azure-core-cpp REQUIRED)
  endif()
endif()

if(BUILD_TESTING)
  # define a symbol that enables some test hooks in code
  add_compile_definitions(TESTING_BUILD)
endif()

set(
  AZURE_IDENTITY_HEADER
    inc/azure/identity/client_secret_credential.hpp
    inc/azure/identity/environment_credential.hpp
    inc/azure/identity/dll_import_export.hpp
    inc/azure/identity/version.hpp
    inc/azure/identity.hpp
)

set(
  AZURE_IDENTITY_SOURCE
    src/client_secret_credential.cpp
    src/environment_credential.cpp
    src/version.cpp
)

add_library(azure-identity ${AZURE_IDENTITY_HEADER} ${AZURE_IDENTITY_SOURCE})

# make sure that users can consume the project as a library.
add_library(Azure::azure-identity ALIAS azure-identity)

create_code_coverage(identity azure-identity azure-identity-test)
create_code_coverage(identity azure-identity-livetest azure-identity-livetest)

target_include_directories(
  azure-identity
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
      $<INSTALL_INTERFACE:include>
      ${azure-core-cpp_INCLUDE_DIRS}
)

target_link_libraries(azure-identity PUBLIC Azure::azure-core)

get_az_version("${CMAKE_CURRENT_SOURCE_DIR}/inc/azure/identity/version.hpp")
generate_documentation(azure-identity ${AZ_LIBRARY_VERSION})

az_vcpkg_export(
    azure-identity
    IDENTITY
    "azure/identity/dll_import_export.hpp"
  )

if(BUILD_TESTING)
  # tests
  if (NOT AZ_ALL_LIBRARIES)
    include(AddGoogleTest)
    enable_testing ()
  endif()

  add_subdirectory(test/live)
  add_subdirectory(test/ut)
endif()

if (BUILD_PERFORMANCE_TESTS)
  add_subdirectory(test/perf)
endif()
