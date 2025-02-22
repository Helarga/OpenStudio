/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"

#include "../../model/SwimmingPoolIndoor.hpp"

#include "../../model/Surface.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Node.hpp"

#include <utilities/idd/SwimmingPool_Indoor_FieldEnums.hxx>
// #include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateSwimmingPoolIndoor(model::SwimmingPoolIndoor& modelObject) {

    // There are a bunch of required fields, so do not register it until everthing looks fine (so not using createRegisterAndNameIdfObject)
    IdfObject idfObject(openstudio::IddObjectType::SwimmingPool_Indoor);

    // Name
    idfObject.setName(modelObject.nameString());

    // Surface Name: Required Object
    Surface surface = modelObject.surface();
    if (!openstudio::istringEqual(surface.surfaceType(), "Floor")) {
      LOG(Error, "Only surfaceTypes of 'Floor' accepted for SwimmingPoolIndoor. " << modelObject.briefDescription() << "'s Surface is "
                                                                                  << surface.briefDescription() << " which has a surface Type of '"
                                                                                  << surface.surfaceType() << "'.");
      return boost::none;
    }

    if (auto _surface = translateAndMapModelObject(surface)) {
      idfObject.setString(SwimmingPool_IndoorFields::SurfaceName, _surface->nameString());
    } else {
      LOG(Error, modelObject.briefDescription() << "'s Surface cannot be translated: " << surface.briefDescription());
    }

    // Average Depth: Required Double
    double averageDepth = modelObject.averageDepth();
    idfObject.setDouble(SwimmingPool_IndoorFields::AverageDepth, averageDepth);

    // Activity Factor Schedule Name: Required Object
    Schedule activityFactorSchedule = modelObject.activityFactorSchedule();
    if (auto _sch = translateAndMapModelObject(activityFactorSchedule)) {
      idfObject.setString(SwimmingPool_IndoorFields::ActivityFactorScheduleName, _sch->nameString());
    } else {
      LOG(Error, "Missing required 'Activity Factor Schedule Name' for " << modelObject.briefDescription());
      return boost::none;
    }

    // Make-up Water Supply Schedule Name: Required Object
    Schedule makeupWaterSupplySchedule = modelObject.makeupWaterSupplySchedule();
    if (auto _sch = translateAndMapModelObject(makeupWaterSupplySchedule)) {
      idfObject.setString(SwimmingPool_IndoorFields::MakeupWaterSupplyScheduleName, _sch->nameString());
    }

    // Cover Schedule Name: Required Object
    Schedule coverSchedule = modelObject.coverSchedule();
    if (auto _sch = translateAndMapModelObject(coverSchedule)) {
      idfObject.setString(SwimmingPool_IndoorFields::CoverScheduleName, _sch->nameString());
    } else {
      LOG(Error, "Missing required 'Cover Schedule Name' for " << modelObject.briefDescription());
      return boost::none;
    }

    // Cover Evaporation Factor: Optional Double
    double coverEvaporationFactor = modelObject.coverEvaporationFactor();
    idfObject.setDouble(SwimmingPool_IndoorFields::CoverEvaporationFactor, coverEvaporationFactor);

    // Cover Convection Factor: Optional Double
    double coverConvectionFactor = modelObject.coverConvectionFactor();
    idfObject.setDouble(SwimmingPool_IndoorFields::CoverConvectionFactor, coverConvectionFactor);

    // Cover Short-Wavelength Radiation Factor: Optional Double
    double coverShortWavelengthRadiationFactor = modelObject.coverShortWavelengthRadiationFactor();
    idfObject.setDouble(SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, coverShortWavelengthRadiationFactor);

    // Cover Long-Wavelength Radiation Factor: Optional Double
    double coverLongWavelengthRadiationFactor = modelObject.coverLongWavelengthRadiationFactor();
    idfObject.setDouble(SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, coverLongWavelengthRadiationFactor);

    // Pool Water Inlet Node: Required Node
    if (boost::optional<Node> _node = modelObject.poolWaterInletNode()) {
      idfObject.setString(SwimmingPool_IndoorFields::PoolWaterInletNode, _node->nameString());
    } else {
      LOG(Error, "Missing required 'Pool Water Inlet Node' for " << modelObject.briefDescription());
    }

    // Pool Water Outlet Node: Required Node
    if (boost::optional<Node> _node = modelObject.poolWaterOutletNode()) {
      idfObject.setString(SwimmingPool_IndoorFields::PoolWaterOutletNode, _node->nameString());
    } else {
      LOG(Error, "Missing required 'Pool Water Outlet Node' for " << modelObject.briefDescription());
    }

    // Pool Heating System Maximum Water Flow Rate
    idfObject.setDouble(SwimmingPool_IndoorFields::PoolHeatingSystemMaximumWaterFlowRate, modelObject.poolHeatingSystemMaximumWaterFlowRate());

    // Pool Miscellaneous Equipment Power
    idfObject.setDouble(SwimmingPool_IndoorFields::PoolMiscellaneousEquipmentPower, modelObject.poolMiscellaneousEquipmentPower());

    // Setpoint Temperature Schedule: Required Object
    Schedule setpointTemperatureSchedule = modelObject.setpointTemperatureSchedule();
    if (auto _sch = translateAndMapModelObject(setpointTemperatureSchedule)) {
      idfObject.setString(SwimmingPool_IndoorFields::SetpointTemperatureSchedule, _sch->nameString());
    } else {
      LOG(Error, "Missing required 'Setpoint Temperature Schedule Name' for " << modelObject.briefDescription());
      return boost::none;
    }

    // Maximum Number of People: Required Double
    double maximumNumberofPeople = modelObject.maximumNumberofPeople();
    idfObject.setDouble(SwimmingPool_IndoorFields::MaximumNumberofPeople, maximumNumberofPeople);

    // People Schedule: Optional Object (but enforced in E+ source)
    Schedule peopleSchedule = modelObject.peopleSchedule();
    if (auto _sch = translateAndMapModelObject(peopleSchedule)) {
      idfObject.setString(SwimmingPool_IndoorFields::PeopleSchedule, _sch->nameString());
    } else {
      LOG(Error, "Missing required 'People Schedule Name' for " << modelObject.briefDescription());
      return boost::none;
    }

    // People Heat Gain Schedule: Optional Object (but enforced in E+ source)
    Schedule peopleHeatGainSchedule = modelObject.peopleHeatGainSchedule();
    if (auto _sch = translateAndMapModelObject(peopleHeatGainSchedule)) {
      idfObject.setString(SwimmingPool_IndoorFields::PeopleHeatGainSchedule, _sch->nameString());
    } else {
      LOG(Error, "Missing required 'People Heat Gain Schedule Name' for " << modelObject.briefDescription());
      return boost::none;
    }

    // We made it, register it
    m_idfObjects.push_back(idfObject);

    return idfObject;

  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
