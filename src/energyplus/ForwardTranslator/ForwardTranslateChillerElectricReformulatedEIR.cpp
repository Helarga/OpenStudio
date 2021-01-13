/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/ChillerElectricReformulatedEIR.hpp"
#include "../../model/ChillerElectricReformulatedEIR_Impl.hpp"
#include "../../model/CurveBiquadratic.hpp"
#include "../../model/CurveBiquadratic_Impl.hpp"
#include "../../model/CurveQuadratic.hpp"
#include "../../model/CurveQuadratic_Impl.hpp"
#include "../../utilities/core/Logger.hpp"
#include "../../utilities/core/Assert.hpp"
#include <utilities/idd/Chiller_Electric_ReformulatedEIR_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateChillerElectricReformulatedEIR(ChillerElectricReformulatedEIR& modelObject) {
    boost::optional<std::string> s;
    boost::optional<double> value;

    IdfObject idfObject(IddObjectType::Chiller_Electric_ReformulatedEIR);

    m_idfObjects.push_back(idfObject);

    // Name

    s = modelObject.name();
    if (s) {
      idfObject.setName(*s);
    }

    // ReferenceCapacity

    if (modelObject.isReferenceCapacityAutosized()) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, "Autosize");
    } else if ((value = modelObject.referenceCapacity())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, value.get());
    }

    // ReferenceCOP

    if ((value = modelObject.referenceCOP())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::ReferenceCOP, value.get());
    }

    // ReferenceLeavingChilledWaterTemperature

    if ((value = modelObject.referenceLeavingChilledWaterTemperature())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingChilledWaterTemperature, value.get());
    }

    // ReferenceEnteringCondenserFluidTemperature

    if ((value = modelObject.referenceEnteringCondenserFluidTemperature())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::ReferenceEnteringCondenserFluidTemperature, value.get());
    }

    // ReferenceChilledWaterFlowRate

    if (modelObject.isReferenceChilledWaterFlowRateAutosized()) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, "Autosize");
    } else if ((value = modelObject.referenceChilledWaterFlowRate())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, value.get());
    }

    // ReferenceCondenserFluidFlowRate

    if (modelObject.isReferenceCondenserFluidFlowRateAutosized()) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserFluidFlowRate, "Autosize");
    } else if ((value = modelObject.referenceCondenserFluidFlowRate())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserFluidFlowRate, value.get());
    }

    // MinimumPartLoadRatio

    if ((value = modelObject.minimumPartLoadRatio())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::MinimumPartLoadRatio, value.get());
    }

    // MaximumPartLoadRatio

    if ((value = modelObject.maximumPartLoadRatio())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::MaximumPartLoadRatio, value.get());
    }

    // OptimumPartLoadRatio

    if ((value = modelObject.optimumPartLoadRatio())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::OptimumPartLoadRatio, value.get());
    }

    // MinimumUnloadingRatio

    if ((value = modelObject.minimumUnloadingRatio())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::MinimumUnloadingRatio, value.get());
    }

    // ChilledWaterInletNodeName

    if (boost::optional<ModelObject> mo = modelObject.supplyInletModelObject()) {
      if (boost::optional<Node> node = mo->optionalCast<Node>()) {
        idfObject.setString(Chiller_Electric_ReformulatedEIRFields::ChilledWaterInletNodeName, node->name().get());
      }
    }

    // ChilledWaterOutletNodeName

    if (boost::optional<ModelObject> mo = modelObject.supplyOutletModelObject()) {
      if (boost::optional<Node> node = mo->optionalCast<Node>()) {
        idfObject.setString(Chiller_Electric_ReformulatedEIRFields::ChilledWaterOutletNodeName, node->name().get());
      }
    }

    // CondenserInletNodeName

    if (boost::optional<ModelObject> mo = modelObject.demandInletModelObject()) {
      if (boost::optional<Node> node = mo->optionalCast<Node>()) {
        idfObject.setString(Chiller_Electric_ReformulatedEIRFields::CondenserInletNodeName, node->name().get());
      }
    }

    // CondenserOutletNodeName

    if (boost::optional<ModelObject> mo = modelObject.demandOutletModelObject()) {
      if (boost::optional<Node> node = mo->optionalCast<Node>()) {
        idfObject.setString(Chiller_Electric_ReformulatedEIRFields::CondenserOutletNodeName, node->name().get());
      }
    }

    // CondenserType
    // The "smart" logic is now handled in model itself
    // (eg: if you connect the chiller to a secondaryPlantLoop, it switches automatically to "WaterCooled")
    idfObject.setString(Chiller_Electric_ReformulatedEIRFields::CondenserType, modelObject.condenserType());

    if (!openstudio::istringEqual(modelObject.condenserType(), "WaterCooled")) {
      {
        // Create an OutdoorAir:NodeList for the condenser inlet conditions to be set directly from weather file
        IdfObject oaNodeListIdf(openstudio::IddObjectType::OutdoorAir_NodeList);
        auto name = modelObject.nameString() + " Inlet Node For Condenser";
        oaNodeListIdf.setString(0, name);
        m_idfObjects.push_back(oaNodeListIdf);
        idfObject.setString(Chiller_Electric_ReformulatedEIRFields::CondenserInletNodeName, name);
      }

      {
        // Name the condenser outlet node
        auto name = modelObject.nameString() + " Outlet Node For Condenser";
        idfObject.setString(Chiller_Electric_ReformulatedEIRFields::CondenserOutletNodeName, name);
      }
    }

    // CondenserFanPowerRatio

    if ((value = modelObject.condenserFanPowerRatio())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::CondenserFanPowerRatio, value.get());
    }

    // CompressorMotorEfficiency
    // Changed to Fraction of Compressor Electric Consumption Rejected by Condenser in E+ version 8.0

    if ((value = modelObject.fractionofCompressorElectricConsumptionRejectedbyCondenser())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, value.get());
    }

    // LeavingChilledWaterLowerTemperatureLimit

    if ((value = modelObject.leavingChilledWaterLowerTemperatureLimit())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::LeavingChilledWaterLowerTemperatureLimit, value.get());
    }

    // ChillerFlowMode

    if ((s = modelObject.chillerFlowMode())) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::ChillerFlowMode, s.get());
    }

    // CoolingCapacityFunctionofTemperatureCurveName

    CurveBiquadratic curve = modelObject.coolingCapacityFunctionOfTemperature();

    boost::optional<IdfObject> _curve = translateAndMapModelObject(curve);

    if (_curve) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::CoolingCapacityFunctionofTemperatureCurveName, _curve->name().get());
    }

    // ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName

    curve = modelObject.electricInputToCoolingOutputRatioFunctionOfTemperature();

    _curve = translateAndMapModelObject(curve);

    if (_curve) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, _curve->name().get());
    }

    // ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName

    CurveQuadratic quadcurve = modelObject.electricInputToCoolingOutputRatioFunctionOfPLR();

    _curve = translateAndMapModelObject(quadcurve);

    if (_curve) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, _curve->name().get());
    }

    // DesignHeatRecoveryWaterFlowRate: If filled, then the Nodes are **required**...
    if (modelObject.heatRecoveryLoop()) {
      if (modelObject.isDesignHeatRecoveryWaterFlowRateAutosized()) {
        idfObject.setString(Chiller_Electric_ReformulatedEIRFields::DesignHeatRecoveryWaterFlowRate, "Autosize");
      } else if ((value = modelObject.designHeatRecoveryWaterFlowRate())) {
        idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::DesignHeatRecoveryWaterFlowRate, value.get());
      }

      // HeatRecoveryInletNodeName
      if (boost::optional<ModelObject> mo = modelObject.tertiaryInletModelObject()) {
        if (boost::optional<Node> node = mo->optionalCast<Node>()) {
          idfObject.setString(Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletNodeName, node->name().get());
        }
      }

      // HeatRecoveryOutletNodeName
      if (boost::optional<ModelObject> mo = modelObject.tertiaryOutletModelObject()) {
        if (boost::optional<Node> node = mo->optionalCast<Node>()) {
          idfObject.setString(Chiller_Electric_ReformulatedEIRFields::HeatRecoveryOutletNodeName, node->name().get());
        }
      }
    }

    // Sizing Factor
    if ((value = modelObject.sizingFactor())) {
      idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::SizingFactor, value.get());
    }

    // Basin Heater Capacity
    idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::BasinHeaterCapacity, modelObject.basinHeaterCapacity());

    // Basin Heater Setpoint Temperature
    idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::BasinHeaterSetpointTemperature, modelObject.basinHeaterSetpointTemperature());

    // Basin Heater Operating Schedule Name
    if (auto _schedule = modelObject.basinHeaterSchedule()) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::BasinHeaterOperatingScheduleName, _schedule->name().get());
    }

    // Condenser Heat Recovery Relative Capacity Fraction
    idfObject.setDouble(Chiller_Electric_ReformulatedEIRFields::CondenserHeatRecoveryRelativeCapacityFraction,
                        modelObject.condenserHeatRecoveryRelativeCapacityFraction());

    // Heat Recovery Inlet High Temperature Limit Schedule Name
    if (auto _schedule = modelObject.heatRecoveryInletHighTemperatureLimitSchedule()) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName, _schedule->name().get());
    }

    // Heat Recovery Leaving Temperature Setpoint Node Name
    if (auto _node = modelObject.heatRecoveryLeavingTemperatureSetpointNode()) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName, _node->name().get());
    }

    // End Use Subcategory
    if ((s = modelObject.endUseSubcategory())) {
      idfObject.setString(Chiller_Electric_ReformulatedEIRFields::EndUseSubcategory, s.get());
    }

    return boost::optional<IdfObject>(idfObject);
  }

}  // namespace energyplus

}  // namespace openstudio
