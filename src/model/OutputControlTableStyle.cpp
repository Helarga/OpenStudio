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

#include "OutputControlTableStyle.hpp"
#include "OutputControlTableStyle_Impl.hpp"

#include <utilities/idd/OS_OutputControl_Table_Style_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

#include "../utilities/units/Unit.hpp"

#include "../utilities/core/Assert.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    OutputControlTableStyle_Impl::OutputControlTableStyle_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == OutputControlTableStyle::iddObjectType());
    }

    OutputControlTableStyle_Impl::OutputControlTableStyle_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model,
                                                               bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == OutputControlTableStyle::iddObjectType());
    }

    OutputControlTableStyle_Impl::OutputControlTableStyle_Impl(const OutputControlTableStyle_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& OutputControlTableStyle_Impl::outputVariableNames() const {
      static const std::vector<std::string> result;
      return result;
    }

    IddObjectType OutputControlTableStyle_Impl::iddObjectType() const {
      return OutputControlTableStyle::iddObjectType();
    }

    std::string OutputControlTableStyle_Impl::columnSeparator() const {
      boost::optional<std::string> value = getString(OS_OutputControl_Table_StyleFields::ColumnSeparator, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool OutputControlTableStyle_Impl::isColumnSeparatorDefaulted() const {
      return isEmpty(OS_OutputControl_Table_StyleFields::ColumnSeparator);
    }

    std::string OutputControlTableStyle_Impl::unitConversion() const {
      boost::optional<std::string> value = getString(OS_OutputControl_Table_StyleFields::UnitConversion, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool OutputControlTableStyle_Impl::isUnitConversionDefaulted() const {
      return isEmpty(OS_OutputControl_Table_StyleFields::UnitConversion);
    }

    bool OutputControlTableStyle_Impl::setColumnSeparator(const std::string& columnSeparator) {
      bool result = setString(OS_OutputControl_Table_StyleFields::ColumnSeparator, columnSeparator);
      return result;
    }

    void OutputControlTableStyle_Impl::resetColumnSeparator() {
      bool result = setString(OS_OutputControl_Table_StyleFields::ColumnSeparator, "");
      OS_ASSERT(result);
    }

    bool OutputControlTableStyle_Impl::setUnitConversion(const std::string& unitConversion) {
      bool result = setString(OS_OutputControl_Table_StyleFields::UnitConversion, unitConversion);
      return result;
    }

    void OutputControlTableStyle_Impl::resetUnitConversion() {
      bool result = setString(OS_OutputControl_Table_StyleFields::UnitConversion, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  IddObjectType OutputControlTableStyle::iddObjectType() {
    return IddObjectType(IddObjectType::OS_OutputControl_Table_Style);
  }

  std::vector<std::string> OutputControlTableStyle::columnSeparatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), OS_OutputControl_Table_StyleFields::ColumnSeparator);
  }

  std::vector<std::string> OutputControlTableStyle::unitConversionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), OS_OutputControl_Table_StyleFields::UnitConversion);
  }

  std::string OutputControlTableStyle::columnSeparator() const {
    return getImpl<detail::OutputControlTableStyle_Impl>()->columnSeparator();
  }

  bool OutputControlTableStyle::isColumnSeparatorDefaulted() const {
    return getImpl<detail::OutputControlTableStyle_Impl>()->isColumnSeparatorDefaulted();
  }

  std::string OutputControlTableStyle::unitConversion() const {
    return getImpl<detail::OutputControlTableStyle_Impl>()->unitConversion();
  }

  bool OutputControlTableStyle::isUnitConversionDefaulted() const {
    return getImpl<detail::OutputControlTableStyle_Impl>()->isUnitConversionDefaulted();
  }

  bool OutputControlTableStyle::setColumnSeparator(const std::string& columnSeparator) {
    return getImpl<detail::OutputControlTableStyle_Impl>()->setColumnSeparator(columnSeparator);
  }

  void OutputControlTableStyle::resetColumnSeparator() {
    getImpl<detail::OutputControlTableStyle_Impl>()->resetColumnSeparator();
  }

  bool OutputControlTableStyle::setUnitConversion(const std::string& unitConversion) {
    return getImpl<detail::OutputControlTableStyle_Impl>()->setUnitConversion(unitConversion);
  }

  void OutputControlTableStyle::resetUnitConversion() {
    getImpl<detail::OutputControlTableStyle_Impl>()->resetUnitConversion();
  }

  /// @cond
  OutputControlTableStyle::OutputControlTableStyle(std::shared_ptr<detail::OutputControlTableStyle_Impl> impl) : ModelObject(std::move(impl)) {}
  OutputControlTableStyle::OutputControlTableStyle(Model& model) : ModelObject(OutputControlTableStyle::iddObjectType(), model) {}

  /// @endcond

}  // namespace model
}  // namespace openstudio
