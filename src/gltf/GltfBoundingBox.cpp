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

#include "GltfBoundingBox.hpp"
#include "../model/PlanarSurfaceGroup.hpp"

#include "../utilities/geometry/BoundingBox.hpp"
#include "../utilities/geometry/Point3d.hpp"
#include "../utilities/geometry/Transformation.hpp"

#include <boost/optional.hpp>
#include <tiny_gltf.h>

#include <map>
#include <string>

namespace openstudio {
namespace gltf {

  GltfBoundingBox::GltfBoundingBox() = default;

  GltfBoundingBox::GltfBoundingBox(const std::vector<model::PlanarSurfaceGroup>& planarSurfaceGroups) {

    // Bounding Box
    std::map<std::string, tinygltf::Value> boundingBoxObject;
    BoundingBox boundingBox;
    boundingBox.addPoint(Point3d(0, 0, 0));
    boundingBox.addPoint(Point3d(1, 1, 1));
    for (const auto& group : planarSurfaceGroups) {
      boundingBox.add(group.transformation() * group.boundingBox());
    }

    double lookAtX = 0;  // (boundingBox.minX().get() + boundingBox.maxX().get()) / 2.0
    double lookAtY = 0;  // (boundingBox.minY().get() + boundingBox.maxY().get()) / 2.0
    double lookAtZ = 0;  // (boundingBox.minZ().get() + boundingBox.maxZ().get()) / 2.0
    double lookAtR =
      sqrt(std::pow(boundingBox.maxX().get() / 2.0, 2) + std::pow(boundingBox.maxY().get() / 2.0, 2) + std::pow(boundingBox.maxZ().get() / 2.0, 2));
    lookAtR = std::max(lookAtR, sqrt(std::pow(boundingBox.minX().get() / 2.0, 2) + std::pow(boundingBox.maxY().get() / 2.0, 2)
                                     + std::pow(boundingBox.maxZ().get() / 2.0, 2)));
    lookAtR = std::max(lookAtR, sqrt(std::pow(boundingBox.maxX().get() / 2.0, 2) + std::pow(boundingBox.minY().get() / 2.0, 2)
                                     + std::pow(boundingBox.maxZ().get() / 2.0, 2)));
    lookAtR = std::max(lookAtR, sqrt(std::pow(boundingBox.maxX().get() / 2.0, 2) + std::pow(boundingBox.maxY().get() / 2.0, 2)
                                     + std::pow(boundingBox.minZ().get() / 2.0, 2)));
    lookAtR = std::max(lookAtR, sqrt(std::pow(boundingBox.minX().get() / 2.0, 2) + std::pow(boundingBox.minY().get() / 2.0, 2)
                                     + std::pow(boundingBox.maxZ().get() / 2.0, 2)));
    lookAtR = std::max(lookAtR, sqrt(std::pow(boundingBox.minX().get() / 2.0, 2) + std::pow(boundingBox.maxY().get() / 2.0, 2)
                                     + std::pow(boundingBox.minZ().get() / 2.0, 2)));
    lookAtR = std::max(lookAtR, sqrt(std::pow(boundingBox.maxX().get() / 2.0, 2) + std::pow(boundingBox.minY().get() / 2.0, 2)
                                     + std::pow(boundingBox.minZ().get() / 2.0, 2)));
    lookAtR = std::max(lookAtR, sqrt(std::pow(boundingBox.minX().get() / 2.0, 2) + std::pow(boundingBox.minY().get() / 2.0, 2)
                                     + std::pow(boundingBox.minZ().get() / 2.0, 2)));

    m_lookAtR = lookAtR;
    m_lookAtX = lookAtX;
    m_lookAtY = lookAtY;
    m_lookAtZ = lookAtZ;
    m_maxX = boundingBox.maxX().get();
    m_maxY = boundingBox.maxY().get();
    m_maxZ = boundingBox.maxZ().get();
    m_minX = boundingBox.minX().get();
    m_minY = boundingBox.minY().get();
    m_minZ = boundingBox.minZ().get();
  }

  double GltfBoundingBox::lookAtR() const {
    return m_lookAtR;
  }
  void GltfBoundingBox::setLookAtR(double lookAtR) {
    m_lookAtR = lookAtR;
  };

  double GltfBoundingBox::lookAtX() const {
    return m_lookAtX;
  }
  void GltfBoundingBox::setLookAtX(double lookAtX) {
    m_lookAtX = lookAtX;
  };

  double GltfBoundingBox::lookAtY() const {
    return m_lookAtY;
  }
  void GltfBoundingBox::setLookAtY(double lookAtY) {
    m_lookAtY = lookAtY;
  };

  double GltfBoundingBox::lookAtZ() const {
    return m_lookAtZ;
  }
  void GltfBoundingBox::setLookAtZ(double lookAtZ) {
    m_lookAtZ = lookAtZ;
  };

  double GltfBoundingBox::maxX() const {
    return m_maxX;
  }
  void GltfBoundingBox::setMaxX(double maxX) {
    m_maxX = maxX;
  };

  double GltfBoundingBox::maxY() const {
    return m_maxY;
  }
  void GltfBoundingBox::setMaxY(double maxY) {
    m_maxY = maxY;
  };

  double GltfBoundingBox::maxZ() const {
    return m_maxZ;
  }
  void GltfBoundingBox::setMaxZ(double maxZ) {
    m_maxZ = maxZ;
  };

  double GltfBoundingBox::minX() const {
    return m_minX;
  }
  void GltfBoundingBox::setMinX(double minX) {
    m_minX = minX;
  };

  double GltfBoundingBox::minY() const {
    return m_minY;
  }
  void GltfBoundingBox::setMinY(double minY) {
    m_minY = minY;
  };

  double GltfBoundingBox::minZ() const {
    return m_minZ;
  }
  void GltfBoundingBox::setMinZ(double minZ) {
    m_minZ = minZ;
  };

  std::map<std::string, tinygltf::Value> GltfBoundingBox::toExtras() const {
    return {
      {"lookAtR", tinygltf::Value(m_lookAtR)}, {"lookAtX", tinygltf::Value(m_lookAtX)}, {"lookAtY", tinygltf::Value(m_lookAtY)},
      {"lookAtZ", tinygltf::Value(m_lookAtZ)}, {"maxX", tinygltf::Value(m_maxX)},       {"maxY", tinygltf::Value(m_maxY)},
      {"maxZ", tinygltf::Value(m_maxZ)},       {"minX", tinygltf::Value(m_minX)},       {"minY", tinygltf::Value(m_minY)},
      {"minZ", tinygltf::Value(m_minZ)},
    };
  }

  GltfBoundingBox::GltfBoundingBox(const tinygltf::Value& boundingBoxObj) {

    if (!boundingBoxObj.IsObject()) {
      LOG_AND_THROW("boundingBoxObj is not a tinygltf Object.");
    }

    for (const auto& key : {"lookAtR", "lookAtX", "lookAtY", "lookAtZ", "maxX", "maxY", "maxZ", "minX", "minY", "minZ"}) {
      if (!boundingBoxObj.Has(key)) {
        LOG(Debug, "boundingBoxObj is missing the key " << key);
      }
    }

    auto tryGetDoubleFromkey = [&boundingBoxObj](const std::string& key) -> boost::optional<double> {
      if (boundingBoxObj.Has(key)) {
        auto val = boundingBoxObj.Get(key);
        if (val.IsReal()) {
          return val.Get<double>();
        } else {
          LOG(Warn, "boundingBoxObj has the key '" << key << "' but it is not a double");
        }
      } else {
        LOG(Debug, "boundingBoxObj is missing the key '" << key << "'");
      }
      return boost::none;
    };

    if (auto d_ = tryGetDoubleFromkey("lookAtR")) {
      m_lookAtR = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("lookAtX")) {
      m_lookAtX = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("lookAtY")) {
      m_lookAtY = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("lookAtZ")) {
      m_lookAtZ = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("maxX")) {
      m_maxX = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("maxY")) {
      m_maxY = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("maxZ")) {
      m_maxZ = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("minX")) {
      m_minX = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("minY")) {
      m_minY = d_.get();
    }

    if (auto d_ = tryGetDoubleFromkey("minZ")) {
      m_minZ = d_.get();
    }
  }

}  // namespace gltf
}  // namespace openstudio
