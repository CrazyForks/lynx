// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "devtool/lynx_devtool/shared_data/white_board_inspector_runtime_delegate.h"

#include "devtool/lynx_devtool/js_debug/js/inspector_java_script_debugger_impl.h"

namespace lynx {
namespace devtool {

WhiteBoardInspectorRuntimeDelegate::WhiteBoardInspectorRuntimeDelegate(
    const std::shared_ptr<InspectorJavaScriptDebuggerImpl>& debugger,
    int view_id)
    : WhiteBoardInspectorDelegate(view_id), js_debugger_(debugger) {}

void WhiteBoardInspectorRuntimeDelegate::SendEvent(const Json::Value& msg) {
  auto sp = js_debugger_.lock();
  CHECK_NULL_AND_LOG_RETURN(
      sp,
      "WhiteBoardInspectorRuntimeDelegate::SendEvent, js_debugger_ is null");
  sp->SendResponse(msg.toStyledString());
}

}  // namespace devtool
}  // namespace lynx
