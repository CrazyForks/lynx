// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_TASM_DELEGATE_H_
#define DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_TASM_DELEGATE_H_

#include <memory>

#include "devtool/lynx_devtool/shared_data/white_board_inspector_delegate.h"

namespace lynx {
namespace devtool {

class InspectorTasmExecutor;
class WhiteBoardInspectorTasmDelegate : public WhiteBoardInspectorDelegate {
 public:
  WhiteBoardInspectorTasmDelegate(
      const std::shared_ptr<InspectorTasmExecutor>& tasm_executor, int view_id);
  ~WhiteBoardInspectorTasmDelegate() override = default;

  // Used only for resetting enabled state after reloading.
  void SetEnabled(bool enable) { enabled_ = enable; }

  void SendEvent(const Json::Value& msg) override;

 private:
  std::weak_ptr<InspectorTasmExecutor> tasm_executor_;
};

}  // namespace devtool
}  // namespace lynx

#endif  // DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_TASM_DELEGATE_H_
