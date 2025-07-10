// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "devtool/lynx_devtool/shared_data/white_board_inspector_tasm_delegate.h"

#include "base/include/log/logging.h"
#include "devtool/lynx_devtool/agent//inspector_tasm_executor.h"
#include "devtool/lynx_devtool/agent/inspector_util.h"

namespace lynx {
namespace devtool {

WhiteBoardInspectorTasmDelegate::WhiteBoardInspectorTasmDelegate(
    const std::shared_ptr<InspectorTasmExecutor>& tasm_executor, int view_id)
    : WhiteBoardInspectorDelegate(view_id), tasm_executor_(tasm_executor) {}

void WhiteBoardInspectorTasmDelegate::SendEvent(const Json::Value& msg) {
  auto sp = tasm_executor_.lock();
  CHECK_NULL_AND_LOG_RETURN(
      sp, "WhiteBoardInspectorTasmDelegate::SendEvent, tasm_executor_ is null");
  sp->SendWhiteBoardEvent(msg);
}

}  // namespace devtool
}  // namespace lynx
