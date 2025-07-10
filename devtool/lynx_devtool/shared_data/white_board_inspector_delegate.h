// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_DELEGATE_H_
#define DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_DELEGATE_H_

#include <memory>

#include "devtool/lynx_devtool/shared_data/white_board_inspector_impl.h"
#include "third_party/jsoncpp/include/json/json.h"

namespace lynx {
namespace devtool {

class WhiteBoardInspectorImpl;

class WhiteBoardInspectorDelegate {
 public:
  explicit WhiteBoardInspectorDelegate(int view_id);
  virtual ~WhiteBoardInspectorDelegate();

  void SetInspector(const std::shared_ptr<WhiteBoardInspectorImpl>& inspector) {
    inspector_ = inspector;
  }

  bool IsEnabled() { return enabled_; }

  std::string Enable(const Json::Value& message);
  std::string Disable(const Json::Value& message);
  std::string SetSharedData(const Json::Value& message);
  std::string GetSharedData(const Json::Value& message);
  std::string RemoveSharedData(const Json::Value& message);
  std::string Clear(const Json::Value& message);

  void OnSharedDataAdded(const std::string& key, const std::string& value);
  void OnSharedDataUpdated(const std::string& key, const std::string& value);
  void OnSharedDataRemoved(const std::string& key);
  void OnSharedDataCleared();

  virtual void SendEvent(const Json::Value& msg) = 0;

 protected:
  std::string GenResponseMessage(int message_id, const Json::Value& result);
  Json::Value GenEventMessage(const std::string& method,
                              const Json::Value& params);
  std::string GenErrorMessage(int message_id, int code,
                              const std::string& message);

  bool enabled_{false};
  int view_id_;
  std::weak_ptr<WhiteBoardInspectorImpl> inspector_;
};

}  // namespace devtool
}  // namespace lynx

#endif  // DEVTOOL_LYNX_DEVTOOL_SHARED_DATA_WHITE_BOARD_INSPECTOR_DELEGATE_H_
