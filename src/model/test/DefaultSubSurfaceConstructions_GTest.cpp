/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "ModelFixture.hpp"

#include "../Model.hpp"
#include "../Model_Impl.hpp"
#include "../Construction.hpp"
#include "../Construction_Impl.hpp"
#include "../DefaultSubSurfaceConstructions.hpp"
#include "../DefaultSubSurfaceConstructions_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, DefaultSubSurfaceConstructions) {
  Model model;

  DefaultSubSurfaceConstructions defaultSubSurfaceConstructions(model);
  Construction construction(model);

  EXPECT_FALSE(defaultSubSurfaceConstructions.fixedWindowConstruction());
  EXPECT_TRUE(defaultSubSurfaceConstructions.setFixedWindowConstruction(construction));
  ASSERT_TRUE(defaultSubSurfaceConstructions.fixedWindowConstruction());
  EXPECT_EQ(construction.handle(), defaultSubSurfaceConstructions.fixedWindowConstruction()->handle());
  defaultSubSurfaceConstructions.resetFixedWindowConstruction();
  EXPECT_FALSE(defaultSubSurfaceConstructions.fixedWindowConstruction());

  EXPECT_FALSE(defaultSubSurfaceConstructions.operableWindowConstruction());
  EXPECT_TRUE(defaultSubSurfaceConstructions.setOperableWindowConstruction(construction));
  ASSERT_TRUE(defaultSubSurfaceConstructions.operableWindowConstruction());
  EXPECT_EQ(construction.handle(), defaultSubSurfaceConstructions.operableWindowConstruction()->handle());
  defaultSubSurfaceConstructions.resetOperableWindowConstruction();
  EXPECT_FALSE(defaultSubSurfaceConstructions.operableWindowConstruction());

  EXPECT_FALSE(defaultSubSurfaceConstructions.doorConstruction());
  EXPECT_TRUE(defaultSubSurfaceConstructions.setDoorConstruction(construction));
  ASSERT_TRUE(defaultSubSurfaceConstructions.doorConstruction());
  EXPECT_EQ(construction.handle(), defaultSubSurfaceConstructions.doorConstruction()->handle());
  defaultSubSurfaceConstructions.resetDoorConstruction();
  EXPECT_FALSE(defaultSubSurfaceConstructions.doorConstruction());

  EXPECT_FALSE(defaultSubSurfaceConstructions.glassDoorConstruction());
  EXPECT_TRUE(defaultSubSurfaceConstructions.setGlassDoorConstruction(construction));
  ASSERT_TRUE(defaultSubSurfaceConstructions.glassDoorConstruction());
  EXPECT_EQ(construction.handle(), defaultSubSurfaceConstructions.glassDoorConstruction()->handle());
  defaultSubSurfaceConstructions.resetGlassDoorConstruction();
  EXPECT_FALSE(defaultSubSurfaceConstructions.glassDoorConstruction());

  EXPECT_FALSE(defaultSubSurfaceConstructions.overheadDoorConstruction());
  EXPECT_TRUE(defaultSubSurfaceConstructions.setOverheadDoorConstruction(construction));
  ASSERT_TRUE(defaultSubSurfaceConstructions.overheadDoorConstruction());
  EXPECT_EQ(construction.handle(), defaultSubSurfaceConstructions.overheadDoorConstruction()->handle());
  defaultSubSurfaceConstructions.resetOverheadDoorConstruction();
  EXPECT_FALSE(defaultSubSurfaceConstructions.overheadDoorConstruction());

  EXPECT_FALSE(defaultSubSurfaceConstructions.skylightConstruction());
  EXPECT_TRUE(defaultSubSurfaceConstructions.setSkylightConstruction(construction));
  ASSERT_TRUE(defaultSubSurfaceConstructions.skylightConstruction());
  EXPECT_EQ(construction.handle(), defaultSubSurfaceConstructions.skylightConstruction()->handle());
  defaultSubSurfaceConstructions.resetSkylightConstruction();
  EXPECT_FALSE(defaultSubSurfaceConstructions.skylightConstruction());

  EXPECT_FALSE(defaultSubSurfaceConstructions.tubularDaylightDomeConstruction());
  EXPECT_TRUE(defaultSubSurfaceConstructions.setTubularDaylightDomeConstruction(construction));
  ASSERT_TRUE(defaultSubSurfaceConstructions.tubularDaylightDomeConstruction());
  EXPECT_EQ(construction.handle(), defaultSubSurfaceConstructions.tubularDaylightDomeConstruction()->handle());
  defaultSubSurfaceConstructions.resetTubularDaylightDomeConstruction();
  EXPECT_FALSE(defaultSubSurfaceConstructions.tubularDaylightDomeConstruction());

  EXPECT_FALSE(defaultSubSurfaceConstructions.tubularDaylightDiffuserConstruction());
  EXPECT_TRUE(defaultSubSurfaceConstructions.setTubularDaylightDiffuserConstruction(construction));
  ASSERT_TRUE(defaultSubSurfaceConstructions.tubularDaylightDiffuserConstruction());
  EXPECT_EQ(construction.handle(), defaultSubSurfaceConstructions.tubularDaylightDiffuserConstruction()->handle());
  defaultSubSurfaceConstructions.resetTubularDaylightDiffuserConstruction();
  EXPECT_FALSE(defaultSubSurfaceConstructions.tubularDaylightDiffuserConstruction());
}
