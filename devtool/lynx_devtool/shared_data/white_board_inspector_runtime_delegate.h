// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_RUNTIME_DELEGATE_H_
#define DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_RUNTIME_DELEGATE_H_

#include <memory>

#include "devtool/lynx_devtool/shared_data/white_board_inspector_delegate.h"

namespace lynx {
namespace devtool {

class InspectorJavaScriptDebuggerImpl;

class WhiteBoardInspectorRuntimeDelegate : public WhiteBoardInspectorDelegate {
 public:
  WhiteBoardInspectorRuntimeDelegate(
      const std::shared_ptr<InspectorJavaScriptDebuggerImpl>& debugger,
      int view_id);
  ~WhiteBoardInspectorRuntimeDelegate() override = default;

  void SendEvent(const Json::Value& msg) override;

 private:
  std::weak_ptr<InspectorJavaScriptDebuggerImpl> js_debugger_;
};

}  // namespace devtool
}  // namespace lynx

#endif  // DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_RUNTIME_DELEGATE_H_
