// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#define protected public
#define private public

#include "devtool/lynx_devtool/shared_data/white_board_inspector_tasm_delegate.h"

#include "devtool/base_devtool/native/test/message_sender_mock.h"
#include "devtool/testing/mock/inspector_tasm_executor_mock.h"
#include "devtool/testing/mock/lynx_devtool_mediator_mock.h"
#include "devtool/testing/mock/lynx_devtool_ng_mock.h"
#include "third_party/googletest/googletest/include/gtest/gtest.h"

namespace lynx {
namespace devtool {
namespace testing {

class WhiteBoardInspectorTasmDelegateTest : public ::testing::Test {
 public:
  WhiteBoardInspectorTasmDelegateTest() {}
  ~WhiteBoardInspectorTasmDelegateTest() override {}
  void SetUp() override {
    devtool_ = std::make_shared<lynx::testing::LynxDevToolNGMock>();
    mediator_ = std::make_shared<lynx::testing::LynxDevToolMediatorMock>();
    message_sender_ = std::make_shared<MessageSenderMock>();
    tasm_executor_ =
        std::make_shared<lynx::testing::InspectorTasmExecutorMock>();
    delegate_ =
        std::make_shared<WhiteBoardInspectorTasmDelegate>(tasm_executor_, 1);
    tasm_executor_->devtool_mediator_wp_ = mediator_;
    mediator_->devtool_wp_ = devtool_;
    devtool_->message_sender_ = message_sender_;
  }

 private:
  std::shared_ptr<WhiteBoardInspectorTasmDelegate> delegate_;
  std::shared_ptr<lynx::testing::InspectorTasmExecutorMock> tasm_executor_;
  std::shared_ptr<lynx::testing::LynxDevToolNGMock> devtool_;
  std::shared_ptr<lynx::testing::LynxDevToolMediatorMock> mediator_;
  std::shared_ptr<MessageSenderMock> message_sender_;
};

TEST_F(WhiteBoardInspectorTasmDelegateTest, SendEvent) {
  Json::Value msg(Json::ValueType::objectValue);
  Json::Value params(Json::ValueType::objectValue);
  params["key"] = "key1";
  params["value"] = "\"value1\"";
  msg["method"] = "WhiteBoard.onSharedDataAdded";
  msg["params"] = params;
  std::string expected = msg.toStyledString();

  delegate_->SendEvent(msg);
  EXPECT_EQ(MockReceiver::GetInstance().received_message_.first, "CDP");
  EXPECT_EQ(MockReceiver::GetInstance().received_message_.second, expected);

  MockReceiver::GetInstance().received_message_ = {"", ""};
  tasm_executor_.reset();
  delegate_->SendEvent(msg);
  EXPECT_EQ(MockReceiver::GetInstance().received_message_.first, "");
  EXPECT_EQ(MockReceiver::GetInstance().received_message_.second, "");
}

}  // namespace testing
}  // namespace devtool
}  // namespace lynx
