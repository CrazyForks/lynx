// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef DEVTOOL_LYNX_DEVTOOL_AGENT_DOMAIN_AGENT_INSPECTOR_WHITE_BOARD_AGENT_H_
#define DEVTOOL_LYNX_DEVTOOL_AGENT_DOMAIN_AGENT_INSPECTOR_WHITE_BOARD_AGENT_H_

#include <memory>
#include <unordered_map>

#include "devtool/base_devtool/native/public/cdp_domain_agent_base.h"
#include "devtool/lynx_devtool/agent/lynx_devtool_mediator.h"

namespace lynx {
namespace devtool {

class InspectorWhiteBoardAgent : public CDPDomainAgentBase {
 public:
  explicit InspectorWhiteBoardAgent(
      const std::shared_ptr<LynxDevToolMediator>& devtool_mediator);
  ~InspectorWhiteBoardAgent() override = default;

  void CallMethod(const std::shared_ptr<MessageSender>& sender,
                  const Json::Value& message) override;

 private:
  typedef void (InspectorWhiteBoardAgent::*WhiteBoardAgentMethod)(
      const std::shared_ptr<MessageSender>& sender, const Json::Value& message);
  void Enable(const std::shared_ptr<MessageSender>& sender,
              const Json::Value& message);
  void Disable(const std::shared_ptr<MessageSender>& sender,
               const Json::Value& message);
  void SetSharedData(const std::shared_ptr<MessageSender>& sender,
                     const Json::Value& message);
  void GetSharedData(const std::shared_ptr<MessageSender>& sender,
                     const Json::Value& message);
  void RemoveSharedData(const std::shared_ptr<MessageSender>& sender,
                        const Json::Value& message);
  void Clear(const std::shared_ptr<MessageSender>& sender,
             const Json::Value& message);

  std::unordered_map<std::string, WhiteBoardAgentMethod> functions_map_;
  std::shared_ptr<LynxDevToolMediator> devtool_mediator_;
};

}  // namespace devtool
}  // namespace lynx

#endif  // DEVTOOL_LYNX_DEVTOOL_AGENT_DOMAIN_AGENT_INSPECTOR_WHITE_BOARD_AGENT_H_
