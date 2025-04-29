// Copyright 2019 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_PUBLIC_PAGE_OPTIONS_H_
#define CORE_PUBLIC_PAGE_OPTIONS_H_

namespace lynx {
namespace tasm {

/// Common options shared by components within a Lynx page.
/// Unlike PageConfig, the options are dynamic and can be updated on-the-flight
/// by calling LynxShell::SetPageOptions
struct PageOptions {
  static constexpr int32_t kUnknownInstanceID = -1;

  PageOptions() = default;

  explicit PageOptions(int32_t instance_id) : instance_id_(instance_id) {}

  void SetInstanceID(int32_t instance_id) { instance_id_ = instance_id; }

  int32_t GetInstanceID() const { return instance_id_; }

  // Set long task monitoring explicitly disabled for this instance.
  // If true, long task monitoring will always be disabled.
  // If false, long task monitoring will respect the default behavior defined by
  // lynx::tasm::timing::LongTaskMonitor
  void SetLongTaskMonitorDisabled(bool disabled) {
    long_task_disabled_ = disabled;
  }

  // Get long task monitoring disabled status for this instance.
  bool GetLongTaskMonitorDisabled() const { return long_task_disabled_; }

 private:
  int32_t instance_id_{kUnknownInstanceID};
  bool long_task_disabled_{false};
};

}  // namespace tasm
}  // namespace lynx

#endif  // CORE_PUBLIC_PAGE_OPTIONS_H_
