// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "core/runtime/jsi/jsvm/jsvm_api.h"

#include <memory>

namespace lynx {
namespace piper {
std::shared_ptr<piper::Runtime> makeJSVMRuntime() { return nullptr; }

std::shared_ptr<profile::RuntimeProfiler> makeJSVMRuntimeProfiler(
    std::shared_ptr<piper::JSIContext> js_context) {
  return nullptr;
}
}  // namespace piper
}  // namespace lynx
