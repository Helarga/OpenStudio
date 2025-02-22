/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_IMPL_HPP
#define MODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_IMPL_HPP

#include "ModelAPI.hpp"
#include "ZoneHVACComponent_Impl.hpp"

namespace openstudio {
namespace model {

  class Schedule;
  class Surface;
  class ThermalZone;
  class HVACComponent;

  namespace detail {

    /** ZoneHVACCoolingPanelRadiantConvectiveWater_Impl is a ZoneHVACComponent_Impl that is the implementation class for ZoneHVACCoolingPanelRadiantConvectiveWater.*/
    class MODEL_API ZoneHVACCoolingPanelRadiantConvectiveWater_Impl : public ZoneHVACComponent_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      ZoneHVACCoolingPanelRadiantConvectiveWater_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      ZoneHVACCoolingPanelRadiantConvectiveWater_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      ZoneHVACCoolingPanelRadiantConvectiveWater_Impl(const ZoneHVACCoolingPanelRadiantConvectiveWater_Impl& other, Model_Impl* model,
                                                      bool keepHandle);

      virtual ~ZoneHVACCoolingPanelRadiantConvectiveWater_Impl() override = default;

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

      boost::optional<ThermalZone> thermalZone() const override;

      bool addToThermalZone(ThermalZone& thermalZone) override;

      void removeFromThermalZone() override;

      virtual ModelObject clone(Model model) const override;

      virtual unsigned inletPort() const override;

      virtual unsigned outletPort() const override;

      virtual std::vector<ModelObject> children() const override;

      virtual std::vector<IdfObject> remove() override;

      virtual ComponentType componentType() const override;
      virtual std::vector<FuelType> coolingFuelTypes() const override;
      virtual std::vector<FuelType> heatingFuelTypes() const override;
      virtual std::vector<AppGFuelType> appGHeatingFuelTypes() const override;

      //@}
      /** @name Getters */
      //@{

      Schedule availabilitySchedule() const;

      double fractionRadiant() const;

      double fractionofRadiantEnergyIncidentonPeople() const;

      HVACComponent coolingCoil() const;

      //@}
      /** @name Setters */
      //@{

      bool setAvailabilitySchedule(Schedule& schedule);

      bool setFractionRadiant(double fractionRadiant);

      bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);

      bool setCoolingCoil(const HVACComponent& coolingCoil);

      //@}
      /** @name Other */
      //@{

      virtual std::vector<EMSActuatorNames> emsActuatorNames() const override;

      virtual std::vector<std::string> emsInternalVariableNames() const override;

      std::vector<Surface> surfaces() const;

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.ZoneHVACCoolingPanelRadiantConvectiveWater");

      // Optional getters for use by methods like children() so can remove() if the constructor fails.
      // There are other ways for the public versions of these getters to fail--perhaps all required
      // objects should be returned as boost::optionals
      boost::optional<Schedule> optionalAvailabilitySchedule() const;
      boost::optional<HVACComponent> optionalCoolingCoil() const;
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_IMPL_HPP
