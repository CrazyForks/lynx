// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "core/renderer/dom/fiber/frame_element.h"

namespace lynx {
namespace tasm {

namespace {
BASE_STATIC_STRING_DECL(kDefaultFrameTag, "frame");
}

FrameElement::FrameElement(ElementManager* manager)
    : FiberElement(manager, kDefaultFrameTag) {}

void FrameElement::OnNodeAdded(FiberElement* child) {
  LOGE("frame element cannot adopt any child");
}

}  // namespace tasm
}  // namespace lynx
