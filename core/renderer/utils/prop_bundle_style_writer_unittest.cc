// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#define private public
#define protected public

#include "core/renderer/utils/prop_bundle_style_writer_unittest.h"

#include "core/renderer/css/computed_css_style.h"
#include "core/renderer/ui_wrapper/common/testing/prop_bundle_mock.h"

namespace lynx {
namespace tasm {
namespace test {

TEST_F(PropBundleStyleWriterTest, TestWriterImpl) {
  PropBundleMock bundle;
  starlight::ComputedCSSStyle style(1, 1);

  style.animation_data_.emplace();
  style.animation_data_->push_back(starlight::AnimationData());

  style.transform_origin_.emplace();
  style.layout_animation_data_.emplace();
  style.enter_transition_data_.emplace();
  style.exit_transition_data_.emplace();
  style.pause_transition_data_.emplace();
  style.resume_transition_data_.emplace();
  style.background_data_.emplace();
  style.mask_data_.emplace();
  style.layout_animation_data_.emplace();
  style.outline_.emplace();
  style.transform_raw_.emplace();
  style.transition_data_.emplace();
  style.box_shadow_.emplace();
  style.text_attributes_.emplace(0);
  style.transform_origin_.emplace();
  style.filter_.emplace();
  style.perspective_data_.emplace();
  style.cursor_.emplace();

#define CALL_STYLE_WRITER(name) \
  PropBundleStyleWriter::Write##name(&bundle, &style);
  FOREACH_PLATFORM_PROPERTY(CALL_STYLE_WRITER);
#undef CALL_STYLE_WRITER
}

}  // namespace test
}  // namespace tasm
}  // namespace lynx
