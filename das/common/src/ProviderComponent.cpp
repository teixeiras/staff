/*
 *  Copyright 2010 Utkin Dmitry
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*
 *  This file is part of the WSF Staff project.
 *  Please, visit http://code.google.com/p/staff for more information.
 */

#include <staff/utils/SharedPtr.h>
#include <staff/component/ServiceWrapper.h>
#include "ProviderComponent.h"

namespace staff
{
namespace das
{
  ProviderComponent::ProviderComponent(const std::string& sName):
    m_sName(sName)
  {
  }

  void ProviderComponent::AddServiceWrapper(const std::string& sServiceName, ServiceWrapper* pServiceWrapper)
  {
    RegisterService(sServiceName, pServiceWrapper);
  }

  const std::string& ProviderComponent::GetName() const
  {
    return m_sName;
  }

}
}
