/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_THREEJSREVERSETRANSLATOR_HPP
#define MODEL_THREEJSREVERSETRANSLATOR_HPP

#include "ModelAPI.hpp"

#include "Model.hpp"

#include "../utilities/geometry/ThreeJS.hpp"
#include "../utilities/core/StringStreamLogSink.hpp"

#include <map>

namespace openstudio {
namespace model {

  class Construction;
  class ConstructionAirBoundary;

  /** ThreeJSReverseTranslator converts a ThreeJS JSON to OpenStudio Model. There are two variations of the ThreeJS format,
    *   this translator requires that the ThreeJS JSON be in OpenStudio Model format rather than optimized for display.
    *
    *   After conversion a map of handles from the ThreeJS JSON to new handles in the returned OpenStudio Model can be retreived.
    *   This map is useful if merging the translated OpenStudio Model with an existing OpenStudio Model.
    */
  class MODEL_API ThreeJSReverseTranslator
  {
   public:
    ThreeJSReverseTranslator();

    /// Convert a ThreeJs Scene to OpenStudio Model format, scene must be in OpenStudio format
    boost::optional<Model> modelFromThreeJS(const ThreeScene& scene);

    /// Mapping between handles referenced in ThreeScene (keys) and handles of objects in returned model (values) for last translation
    /// This handle mapping can be used by the ModelMerger when merging returned model (new handles) with an existing model (existing handles)
    /// Note that this mapping may not include all objects such as Site, Building, or other objects not specified in the ThreeScene
    std::map<UUID, UUID> handleMapping() const;

    /// Get warning messages generated by the last translation.
    std::vector<LogMessage> warnings() const;

    /// Get error messages generated by the last translation.
    std::vector<LogMessage> errors() const;

   private:
    REGISTER_LOGGER("openstudio.model.ThreeJSReverseTranslator");

    Point3dVectorVector getFaces(const ThreeGeometryData& data) const;

    ConstructionAirBoundary getAirWallConstruction(Model& model);

    std::map<UUID, UUID> m_handleMapping;

    StringStreamLogSink m_logSink;
  };

}  // namespace model
}  // namespace openstudio
#endif  //MODEL_THREEJSREVERSETRANSLATOR_HPP
