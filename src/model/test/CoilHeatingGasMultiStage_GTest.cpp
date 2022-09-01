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

#include <gtest/gtest.h>

#include "ModelFixture.hpp"

#include "../CoilHeatingGasMultiStage.hpp"
#include "../CoilHeatingGasMultiStage_Impl.hpp"
#include "../CoilHeatingGasMultiStageStageData.hpp"
#include "../CoilHeatingGasMultiStageStageData_Impl.hpp"
#include "../ScheduleConstant.hpp"
#include "../ScheduleConstant_Impl.hpp"
#include "../CurveQuadratic.hpp"
#include "../CurveQuadratic_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, CoilHeatingGasMultiStage_GettersSetters) {
  Model m;
  CoilHeatingGasMultiStage coil(m);

  EXPECT_FALSE(coil.availabilitySchedule());
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_FALSE(coil.parasiticGasLoad());
  EXPECT_EQ(0u, coil.stages().size());

  ScheduleConstant scheduleConstant(m);
  EXPECT_TRUE(coil.setAvailabilitySchedule(scheduleConstant));
  CurveQuadratic curveQuadratic(m);
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(curveQuadratic));
  EXPECT_TRUE(coil.setParasiticGasLoad(100.0));

  ASSERT_TRUE(coil.availabilitySchedule());
  EXPECT_EQ(scheduleConstant.handle(), coil.availabilitySchedule().get().handle());
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve());
  EXPECT_EQ(curveQuadratic.handle(), coil.partLoadFractionCorrelationCurve().get().handle());
  ASSERT_TRUE(coil.parasiticGasLoad());
  EXPECT_EQ(100.0, coil.parasiticGasLoad().get());

  coil.resetAvailabilitySchedule();
  coil.resetPartLoadFractionCorrelationCurve();
  coil.resetParasiticGasLoad();

  EXPECT_FALSE(coil.availabilitySchedule());
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_FALSE(coil.parasiticGasLoad());
  EXPECT_EQ(0u, coil.stages().size());
}

TEST_F(ModelFixture, CoilHeatingGasMultiStage_Remove) {
  Model m;
  CoilHeatingGasMultiStage coil(m);
  CoilHeatingGasMultiStageStageData stage(m);
  coil.addStage(stage);
  coil.remove();

  EXPECT_EQ(0u, m.modelObjects().size());
}
