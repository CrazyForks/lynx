// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#define protected public
#define private public

#include "devtool/lynx_devtool/shared_data/white_board_inspector_runtime_delegate.h"

#include "devtool/base_devtool/native/test/message_sender_mock.h"
#include "devtool/lynx_devtool/js_debug/js/inspector_java_script_debugger_impl.h"
#include "devtool/testing/mock/lynx_devtool_mediator_mock.h"
#include "devtool/testing/mock/lynx_devtool_ng_mock.h"
#include "third_party/googletest/googletest/include/gtest/gtest.h"

namespace lynx {
namespace devtool {
namespace testing {

class WhiteBoardInspectorRuntimeDelegateTest : public ::testing::Test {
 public:
  WhiteBoardInspectorRuntimeDelegateTest() {}
  ~WhiteBoardInspectorRuntimeDelegateTest() override {}
  void SetUp() override {
    debugger_ = std::make_shared<InspectorJavaScriptDebuggerImpl>(nullptr, 1);
    delegate_ =
        std::make_shared<WhiteBoardInspectorRuntimeDelegate>(debugger_, 1);
  }

 private:
  std::shared_ptr<WhiteBoardInspectorRuntimeDelegate> delegate_;
  std::shared_ptr<InspectorJavaScriptDebuggerImpl> debugger_;
};

TEST_F(WhiteBoardInspectorRuntimeDelegateTest, SendEvent) {
  Json::Value msg(Json::ValueType::objectValue);
  Json::Value params(Json::ValueType::objectValue);
  params["key"] = "key1";
  params["value"] = "\"value1\"";
  msg["method"] = "WhiteBoard.onSharedDataAdded";
  msg["params"] = params;
  std::string expected = msg.toStyledString();

  delegate_->SendEvent(msg);
  EXPECT_EQ(debugger_->message_buf_.front(), expected);

  // test the case when js_debugger_ is nullptr
  debugger_.reset();
  delegate_->SendEvent(msg);
}

}  // namespace testing
}  // namespace devtool
}  // namespace lynx
