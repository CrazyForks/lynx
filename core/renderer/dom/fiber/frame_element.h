// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RENDERER_DOM_FIBER_FRAME_ELEMENT_H_
#define CORE_RENDERER_DOM_FIBER_FRAME_ELEMENT_H_

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "core/renderer/dom/element_manager.h"
#include "core/renderer/dom/fiber/fiber_element.h"

namespace lynx {
namespace tasm {
class FrameElement : public FiberElement {
 public:
  FrameElement(ElementManager* manager);
  ~FrameElement() override = default;

 protected:
  void OnNodeAdded(FiberElement* child) override;
};
}  // namespace tasm
}  // namespace lynx

#endif  // CORE_RENDERER_DOM_FIBER_FRAME_ELEMENT_H_
