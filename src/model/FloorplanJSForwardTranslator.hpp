/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_FLOORPLANJSFORWARDTRANSLATOR_HPP
#define MODEL_FLOORPLANJSFORWARDTRANSLATOR_HPP

#include "ModelAPI.hpp"

#include "Model.hpp"

#include "../utilities/geometry/FloorplanJS.hpp"
#include "../utilities/core/Logger.hpp"
#include "../utilities/core/StringStreamLogSink.hpp"

namespace openstudio {
namespace model {

  /** FloorplanJSForwardTranslator updates a FloorspaceJS JSON with content from an OpenStudio Model. This update does not
    *   convert OpenStudio Model geometry to FloorspaceJS format.  The update is only for non-geometrical data.  For example,
    *   a Space's name and handle may be updated in the FloorspaceJS JSON but a Space's floorprint will not be updated.
    */
  class MODEL_API FloorplanJSForwardTranslator
  {
   public:
    FloorplanJSForwardTranslator();

    /// Update FloorplanJS to match OpenStudio Model
    FloorplanJS updateFloorplanJS(const FloorplanJS& floorplan, const Model& model, bool removeMissingObjects);

    /// Get warning messages generated by the last translation.
    std::vector<LogMessage> warnings() const;

    /// Get error messages generated by the last translation.
    std::vector<LogMessage> errors() const;

   private:
    REGISTER_LOGGER("openstudio.model.FloorplanJSForwardTranslator");

    StringStreamLogSink m_logSink;
  };

}  // namespace model
}  // namespace openstudio
#endif  //MODEL_FLOORPLANJSFORWARDTRANSLATOR_HPP
