// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include <azure/keyvault/common/keyvault_exception.hpp>

#include "azure/keyvault/keys/details/key_constants.hpp"
#include "azure/keyvault/keys/details/key_serializers.hpp"
#include "azure/keyvault/keys/recover_deleted_key_operation.hpp"

using namespace Azure::Security::KeyVault::Keys;
using namespace Azure::Security::KeyVault;

std::unique_ptr<Azure::Core::Http::RawResponse>
Azure::Security::KeyVault::Keys::RecoverDeletedKeyOperation::PollInternal(
    Azure::Core::Context& context)
{
  std::unique_ptr<Azure::Core::Http::RawResponse> rawResponse;
  if (!IsDone())
  {
    rawResponse = m_pipeline->Send(
        context,
        Azure::Core::Http::HttpMethod::Get,
        {_detail::KeysPath, m_value.Name(), m_value.Properties.Version});

    switch (rawResponse->GetStatusCode())
    {
      case Azure::Core::Http::HttpStatusCode::Ok:
      // Access denied but proof the key was deleted.
      case Azure::Core::Http::HttpStatusCode::Forbidden: {
        m_status = Azure::Core::OperationStatus::Succeeded;
        break;
      }
      case Azure::Core::Http::HttpStatusCode::NotFound: {
        m_status = Azure::Core::OperationStatus::Running;
        break;
      }
      default:
        throw Azure::Security::KeyVault::_detail::KeyVaultException::CreateException(
            std::move(rawResponse));
    }
    if (m_status == Azure::Core::OperationStatus::Succeeded)
    {
      m_value
          = _detail::KeyVaultKeySerializer::KeyVaultKeyDeserialize(m_value.Name(), *rawResponse);
    }
  }

  // To ensure the success of calling Poll multiple times, even after operation is completed, a
  // copy of the raw http response is returned instead of transfering the ownership of the raw
  // response inside the Operation.
  return rawResponse;
}

Azure::Security::KeyVault::Keys::RecoverDeletedKeyOperation::RecoverDeletedKeyOperation(
    std::shared_ptr<Azure::Security::KeyVault::_internal::KeyVaultPipeline> keyvaultPipeline,
    Azure::Response<Azure::Security::KeyVault::Keys::KeyVaultKey> response)
    : m_pipeline(keyvaultPipeline)
{
  // The response becomes useless and the value and rawResponse are now owned by the
  // DeleteKeyOperation. This is fine because the DeleteKeyOperation is what the delete key api
  // will return.
  m_value = response.Value;
  m_rawResponse = std::move(response.RawResponse);

  // The key name is enough to resume the operation
  m_continuationToken = m_value.Name();
}
