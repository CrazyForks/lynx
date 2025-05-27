// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef BASE_INCLUDE_AUTO_CREATE_OPTIONAL_H_
#define BASE_INCLUDE_AUTO_CREATE_OPTIONAL_H_

#include <memory>

namespace lynx {
namespace base {

template <typename T>
class auto_create_optional {
 public:
  T& operator*() const { return *create_if_null(); }

  T* operator->() const { return create_if_null(); }

  T* get() const { return data_.get(); }

  void reset() { data_.reset(); }

  bool has_value() const noexcept { return data_ != nullptr; }

  explicit operator bool() const noexcept { return has_value(); }

 private:
  mutable std::unique_ptr<T> data_;

  T* create_if_null() const {
    if (!data_) {
      data_ = std::make_unique<T>();
    }
    return data_.get();
  }
};

}  // namespace base
}  // namespace lynx

#endif  // BASE_INCLUDE_AUTO_CREATE_OPTIONAL_H_
