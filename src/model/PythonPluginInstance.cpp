/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2022, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#include "PythonPluginInstance.hpp"
#include "PythonPluginInstance_Impl.hpp"

#include "ExternalFile.hpp"
#include "ExternalFile_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_PythonPlugin_Instance_FieldEnums.hxx>

#include "../utilities/units/Unit.hpp"
#include "../utilities/core/Assert.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    PythonPluginInstance_Impl::PythonPluginInstance_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PythonPluginInstance::iddObjectType());
    }

    PythonPluginInstance_Impl::PythonPluginInstance_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PythonPluginInstance::iddObjectType());
    }

    PythonPluginInstance_Impl::PythonPluginInstance_Impl(const PythonPluginInstance_Impl& other, Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(other, model, keepHandle) {}



    ExternalFile PythonPluginInstance_Impl::externalFile() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<ExternalFile>(OS_PythonPlugin_InstanceFields::ExternalFileName);
      OS_ASSERT(value);
      return value.get();
    }



  }  // namespace detail

  PythonPluginInstance::PythonPluginInstance(const ExternalFile& externalfile)
    : ResourceObject(PythonPluginInstance::iddObjectType(), externalfile.model()) {
    OS_ASSERT(getImpl<detail::PythonPluginInstance_Impl>());
    bool ok;
    ok = setPointer(OS_PythonPlugin_InstanceFields::ExternalFileName, externalfile.handle());
    OS_ASSERT(ok);

  }



  ExternalFile PythonPluginInstance::externalFile() const {
    return getImpl<detail::PythonPluginInstance_Impl>()->externalFile();
  }



  /// @cond
  PythonPluginInstance::PythonPluginInstance(std::shared_ptr<detail::PythonPluginInstance_Impl> impl) : ResourceObject(impl) {}
  /// @endcond

}  // namespace model
}  // namespace openstudio
