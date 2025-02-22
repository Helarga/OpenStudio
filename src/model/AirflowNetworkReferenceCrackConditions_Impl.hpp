/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_AIRFLOWNETWORKREFERENCECRACKCONDITIONS_IMPL_HPP
#define MODEL_AIRFLOWNETWORKREFERENCECRACKCONDITIONS_IMPL_HPP

#include "ModelAPI.hpp"
#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    /** AirflowNetworkReferenceCrackConditions_Impl is a ModelObject_Impl that is the implementation class for AirflowNetworkReferenceCrackConditions.*/
    class MODEL_API AirflowNetworkReferenceCrackConditions_Impl : public ModelObject_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      AirflowNetworkReferenceCrackConditions_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      AirflowNetworkReferenceCrackConditions_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      AirflowNetworkReferenceCrackConditions_Impl(const AirflowNetworkReferenceCrackConditions_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~AirflowNetworkReferenceCrackConditions_Impl() override = default;

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      //@}
      /** @name Getters */
      //@{

      double referenceTemperature() const;

      bool isReferenceTemperatureDefaulted() const;

      double referenceBarometricPressure() const;

      bool isReferenceBarometricPressureDefaulted() const;

      double referenceHumidityRatio() const;

      bool isReferenceHumidityRatioDefaulted() const;

      //@}
      /** @name Setters */
      //@{

      void setReferenceTemperature(double referenceTemperature);

      void resetReferenceTemperature();

      bool setReferenceBarometricPressure(double referenceBarometricPressure);

      void resetReferenceBarometricPressure();

      void setReferenceHumidityRatio(double referenceHumidityRatio);

      void resetReferenceHumidityRatio();

      //@}
      /** @name Other */
      //@{

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.AirflowNetworkReferenceCrackConditions");
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_AIRFLOWNETWORKREFERENCECRACKCONDITIONS_IMPL_HPP
