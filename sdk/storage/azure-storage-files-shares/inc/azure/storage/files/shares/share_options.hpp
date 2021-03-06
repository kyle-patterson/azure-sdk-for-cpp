// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <azure/core/internal/client_options.hpp>
#include <azure/core/nullable.hpp>
#include <azure/storage/common/access_conditions.hpp>

#include "azure/storage/files/shares/protocol/share_rest_client.hpp"

namespace Azure { namespace Storage { namespace Files { namespace Shares {

  /**
   * @brief Client options used to initalize ShareServiceClient, ShareClient, ShareFileClient and
   * ShareDirectoryClient.
   */
  struct ShareClientOptions : Azure::Core::_internal::ClientOptions
  {
    /**
     * API version used by this client.
     */
    std::string ApiVersion = _detail::DefaultServiceApiVersion;
  };

  struct ListSharesOptions
  {
    /**
     * @brief Filters the results to return only entries whose name begins with the specified
     * prefix.
     */
    Azure::Nullable<std::string> Prefix;

    /**
     * @brief A string value that identifies the portion of the list to be returned with the next
     * list operation. The operation returns a marker value within the response body if the list
     * returned was not complete. The marker value may then be used in a subsequent call to request
     * the next set of list items. The marker value is opaque to the client.
     */
    Azure::Nullable<std::string> ContinuationToken;

    /**
     * @brief Specifies the maximum number of entries to return. If the request does not specify
     * PageSizeHint, or specifies a value greater than 5,000, the server will return up to 5,000
     * items.
     */
    Azure::Nullable<int32_t> PageSizeHint;

    /**
     * @brief Include this parameter to specify one or more datasets to include in the response.
     */
    Azure::Nullable<Models::ListSharesIncludeFlags> ListSharesIncludeFlags;
  };

  struct SetServicePropertiesOptions
  {
  };

  struct GetServicePropertiesOptions
  {
  };

  struct CreateShareOptions
  {
    /**
     * @brief A name-value pair to associate with a file storage object.
     */
    Storage::Metadata Metadata;

    /**
     * @brief Specifies the access tier of the share. This is only valid for standard file account
     * and the value can only be one of `Hot`, `Cool` or `TransactionOptimized`
     */
    Azure::Nullable<Models::AccessTier> AccessTier;

    /**
     * @brief Specifies the maximum size of the share, in gigabytes.
     */
    Azure::Nullable<int64_t> ShareQuotaInGiB;
  };

  struct DeleteShareOptions
  {
    /**
     * @brief Specifies the option include to delete the base share and all of its snapshots.
     */
    Azure::Nullable<bool> DeleteSnapshots;
  };

  struct CreateShareSnapshotOptions
  {
    /**
     * @brief The metadata to be set on the snapshot of the share.
     */
    Storage::Metadata Metadata;
  };

  struct GetSharePropertiesOptions
  {
  };

  struct SetSharePropertiesOptions
  {
    /**
     * @brief Specifies the access tier of the share. This is only valid for standard file account
     * and the value can only be one of `Hot`, `Cool` or `TransactionOptimized`
     */
    Azure::Nullable<Models::AccessTier> AccessTier;

    /**
     * @brief Specifies the maximum size of the share, in gigabytes.
     */
    Azure::Nullable<int64_t> ShareQuotaInGiB;
  };

  struct SetShareMetadataOptions
  {
  };

  struct GetShareAccessPolicyOptions
  {
  };

  struct SetShareAccessPolicyOptions
  {
  };

  struct GetShareStatisticsOptions
  {
  };

  struct CreateSharePermissionOptions
  {
  };

  struct GetSharePermissionOptions
  {
  };

  /**
   * @brief Optional parameters for ShareClient::AcquireLease.
   */
  struct AcquireLeaseOptions
  {
  };

  /**
   * @brief Optional parameters for ShareClient::ChangeLease.
   */
  struct ChangeLeaseOptions
  {
  };

  /**
   * @brief Optional parameters for ShareClient::ReleaseLease.
   */
  struct ReleaseLeaseOptions
  {
  };

  /**
   * @brief Optional parameters for ShareClient::BreakLease.
   */
  struct BreakLeaseOptions
  {
    /**
     * @brief Proposed duration the lease should continue before it is broken, in seconds,
     * between 0 and 60. This break period is only used if it is shorter than the time remaining on
     * the lease. If longer, the time remaining on the lease is used. A new lease will not be
     * available before the break period has expired, but the lease may be held for longer than the
     * break period.
     */
    Azure::Nullable<int32_t> BreakPeriod;
  };

  /**
   * @brief Optional parameters for ShareClient::BreakLease.
   */
  struct RenewLeaseOptions
  {
  };

  struct CreateDirectoryOptions
  {
    /**
     * @brief A name-value pair to associate with a directory object.
     */
    Storage::Metadata Metadata;

    /**
     * @brief This permission is the security descriptor for the directory specified in the Security
     * Descriptor Definition Language (SDDL). If not specified, 'inherit' is used.
     */
    Azure::Nullable<std::string> DirectoryPermission;

    /**
     * @brief SMB properties to set for the directory.
     */
    Models::FileSmbProperties SmbProperties;
  };

  struct DeleteDirectoryOptions
  {
  };

  struct GetDirectoryPropertiesOptions
  {
  };

  struct SetDirectoryPropertiesOptions
  {
    /**
     * @brief If specified the permission (security descriptor) shall be set for the directory.
     * This option can be used if Permission size is <= 8KB, else SmbProperties.PermissionKey
     * shall be used. Default value: 'inherit'. If SDDL is specified as input, it must have owner,
     * group and dacl.
     */
    Azure::Nullable<std::string> FilePermission;
  };

  struct SetDirectoryMetadataOptions
  {
  };

  struct ListFilesAndDirectoriesOptions
  {
    /**
     * @brief Filters the results to return only entries whose name begins with the specified
     * prefix.
     */
    Azure::Nullable<std::string> Prefix;

    /**
     * @brief A string value that identifies the portion of the list to be returned with the next
     * list operation. The operation returns a marker value within the response body if the list
     * returned was not complete. The marker value may then be used in a subsequent call to request
     * the next set of list items. The marker value is opaque to the client.
     */
    Azure::Nullable<std::string> ContinuationToken;

    /**
     * @brief Specifies the maximum number of entries to return. If the request does not specify
     * PageSizeHint, or specifies a value greater than 5,000, the server will return up to 5,000
     * items.
     */
    Azure::Nullable<int32_t> PageSizeHint;
  };

  struct ListDirectoryHandlesOptions
  {
    /**
     * @brief A string value that identifies the portion of the list to be returned with the next
     * list operation. The operation returns a marker value within the response body if the list
     * returned was not complete. The marker value may then be used in a subsequent call to request
     * the next set of list items. The marker value is opaque to the client.
     */
    Azure::Nullable<std::string> ContinuationToken;

    /**
     * @brief Specifies the maximum number of entries to return. If the request does not specify
     * PageSizeHint, or specifies a value greater than 5,000, the server will return up to 5,000
     * items.
     */
    Azure::Nullable<int32_t> PageSizeHint;

    /**
     * @brief Specifies operation should apply to the directory specified in the URI, its files, its
     * subdirectories and their files.
     */
    Azure::Nullable<bool> Recursive;
  };

  struct ForceCloseDirectoryHandleOptions
  {
  };

  struct CreateFileOptions
  {
    /**
     * @brief This permission is the security descriptor for the file specified in the Security
     * Descriptor Definition Language (SDDL). If not specified, 'inherit' is used.
     */
    Azure::Nullable<std::string> Permission;

    /**
     * @brief SMB properties to set for the file.
     */
    Models::FileSmbProperties SmbProperties;

    /**
     * @brief Specifies the HttpHeaders of the file.
     */
    Models::FileHttpHeaders HttpHeaders;

    /**
     * @brief A name-value pair to associate with a file storage object.
     */
    Storage::Metadata Metadata;

    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct DeleteFileOptions
  {
    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct DownloadFileOptions
  {
    /**
     * @brief Downloads only the bytes of the file from this range.
     */
    Azure::Nullable<Core::Http::HttpRange> Range;

    /**
     * @brief When specified together with Range, service returns hash for the range as long as the
     * range is less than or equal to 4 MiB in size. Only MD5 is supported for now.
     */
    Azure::Nullable<HashAlgorithm> RangeHashAlgorithm;

    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct StartFileCopyOptions
  {
    /**
     * @brief A name-value pair to associate with a file storage object.
     */
    Storage::Metadata Metadata;

    /**
     * @brief This permission is the security descriptor for the file specified in the Security
     * Descriptor Definition Language (SDDL). If not specified, 'inherit' is used.
     */
    Azure::Nullable<std::string> Permission;

    /**
     * @brief SMB properties to set for the destination file.
     */
    Models::FileSmbProperties SmbProperties;

    /**
     * @brief Specifies the option to copy file security descriptor from source file or to set it
     * using the value which is defined by the smb properties.
     */
    Azure::Nullable<Models::PermissionCopyMode> PermissionCopyMode;

    /**
     * @brief Specifies the option to overwrite the target file if it already exists and has
     * read-only attribute set.
     */
    Azure::Nullable<bool> IgnoreReadOnly;

    /**
     * @brief Specifies the option to set archive attribute on a target file. True means archive
     * attribute will be set on a target file despite attribute overrides or a source file state.
     */
    Azure::Nullable<bool> SetArchiveAttribute;

    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct AbortFileCopyOptions
  {
    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct GetFilePropertiesOptions
  {
    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct SetFilePropertiesOptions
  {
    /**
     * @brief This permission is the security descriptor for the file specified in the Security
     * Descriptor Definition Language (SDDL). If not specified, 'inherit' is used.
     */
    Azure::Nullable<std::string> Permission;

    /**
     * @brief Specify this to resize a file to the specified value.
     */
    Azure::Nullable<int64_t> Size;

    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct SetFileMetadataOptions
  {
    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct UploadFileRangeOptions
  {
    /**
     * @brief An MD5 hash of the content. This hash is used to verify the integrity of the data
     * during transport. When the TransactionalContentHash parameter is specified, the File service
     * compares the hash of the content that has arrived with the header value that was sent. If the
     * two hashes do not match, the operation will fail with error code 400 (Bad Request).
     */
    Azure::Nullable<ContentHash> TransactionalContentHash;

    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct ClearFileRangeOptions
  {
    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct UploadFileRangeFromUriOptions
  {
    /**
     * @brief Specify the hash calculated for the range of bytes that must be read from the copy
     * source.
     */
    Azure::Nullable<ContentHash> TransactionalContentHash;

    /**
     * @brief Specify the access condition for the source. Only ContentHash with Crc64 is supported.
     */
    ContentHashAccessConditions SourceAccessCondition;

    /**
     * @brief The operation will only succeed if the lease access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct GetFileRangeListOptions
  {
    /**
     * @brief The range to be get from service.
     */
    Azure::Nullable<Core::Http::HttpRange> Range;

    /**
     * @brief The operation will only succeed if the access condition is met.
     */
    LeaseAccessConditions AccessConditions;
  };

  struct ListFileHandlesOptions
  {
    /**
     * @brief A string value that identifies the portion of the list to be returned with the next
     * list operation. The operation returns a marker value within the response body if the list
     * returned was not complete. The marker value may then be used in a subsequent call to request
     * the next set of list items. The marker value is opaque to the client.
     */
    Azure::Nullable<std::string> ContinuationToken;

    /**
     * @brief Specifies the maximum number of entries to return. If the request does not specify
     * PageSizeHint, or specifies a value greater than 5,000, the server will return up to 5,000
     * items.
     */
    Azure::Nullable<int32_t> PageSizeHint;
  };

  struct ForceCloseFileHandleOptions
  {
  };

  /**
   * @brief Optional parameters for FileClient::DownloadTo.
   */
  struct DownloadFileToOptions
  {
    /**
     * @brief Downloads only the bytes of the file from this range.
     */
    Azure::Nullable<Core::Http::HttpRange> Range;

    struct
    {
      /**
       * @brief The size of the first range request in bytes. Files smaller than this limit will be
       * downloaded in a single request. Files larger than this limit will continue being downloaded
       * in chunks of size ChunkSize.
       */
      int64_t InitialChunkSize = 256 * 1024 * 1024;

      /**
       * @brief The maximum number of bytes in a single request.
       */
      int64_t ChunkSize = 4 * 1024 * 1024;

      /**
       * @brief The maximum number of threads that may be used in a parallel transfer.
       */
      int Concurrency = 5;
    } TransferOptions;
  };

  /**
   * @brief Optional parameters for FileClient::UploadFrom.
   */
  struct UploadFileFromOptions
  {
    /**
     * @brief The standard HTTP header system properties to set.
     */
    Models::FileHttpHeaders HttpHeaders;

    /**
     * @brief Name-value pairs associated with the file as metadata.
     */
    Storage::Metadata Metadata;

    /**
     * @brief SMB properties to set for the destination file.
     */
    Models::FileSmbProperties SmbProperties;

    /**
     * @brief If specified the permission (security descriptor) shall be set for the directory.
     * This option can be used if Permission size is <= 8KB, else SmbProperties.PermissionKey
     * shall be used. Default value: 'inherit'. If SDDL is specified as input, it must have owner,
     * group and dacl.
     */
    Azure::Nullable<std::string> FilePermission;

    struct
    {
      /**
       * @brief File smaller than this will be uploaded with a single upload operation. This value
       * cannot be larger than 4 MiB.
       */
      int64_t SingleUploadThreshold = 4 * 1024 * 1024;

      /**
       * @brief The maximum number of bytes in a single request.
       */
      int64_t ChunkSize = 4 * 1024 * 1024;

      /**
       * @brief The maximum number of threads that may be used in a parallel transfer.
       */
      int Concurrency = 5;
    } TransferOptions;
  };
}}}} // namespace Azure::Storage::Files::Shares
