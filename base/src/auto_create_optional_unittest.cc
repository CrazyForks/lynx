// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include <string>
#include <vector>

#define private public

#include "base/include/auto_create_optional.h"
#include "third_party/googletest/googletest/include/gtest/gtest.h"

namespace lynx {
namespace base {
namespace test {

struct DataStruct {
  std::vector<std::string> vec1;
  std::vector<std::string> vec2;
};

TEST(AutoCreateOptional, CreateByArrow) {
  auto_create_optional<DataStruct> data;
  EXPECT_FALSE(data.has_value());
  EXPECT_FALSE(bool(data));
  EXPECT_EQ(data.get(), nullptr);

  data->vec1.push_back("123");
  data->vec2.push_back("abc");

  EXPECT_TRUE(data.has_value());
  EXPECT_TRUE(bool(data));

  EXPECT_EQ(&(data.data_->vec1), &(data.get()->vec1));
  EXPECT_EQ(&(data.data_->vec1), &((*data).vec1));
  EXPECT_TRUE(data.data_->vec1.size() == 1);
  EXPECT_TRUE(data.data_->vec1[0] == "123");
  EXPECT_TRUE(data.data_->vec2.size() == 1);
  EXPECT_TRUE(data.data_->vec2[0] == "abc");

  data.reset();
  EXPECT_FALSE(data.has_value());
  EXPECT_FALSE(bool(data));
  EXPECT_EQ(data.get(), nullptr);

  data->vec1.push_back("123");
  data->vec2.push_back("abc");

  EXPECT_TRUE(data.has_value());
  EXPECT_TRUE(bool(data));

  EXPECT_EQ(&(data.data_->vec1), &(data.get()->vec1));
  EXPECT_EQ(&(data.data_->vec1), &((*data).vec1));
  EXPECT_TRUE(data.data_->vec1.size() == 1);
  EXPECT_TRUE(data.data_->vec1[0] == "123");
  EXPECT_TRUE(data.data_->vec2.size() == 1);
  EXPECT_TRUE(data.data_->vec2[0] == "abc");
}

TEST(AutoCreateOptional, CreateByAsterisk) {
  auto_create_optional<std::vector<std::string>> data;
  EXPECT_FALSE(data.has_value());
  EXPECT_FALSE(bool(data));
  EXPECT_EQ(data.get(), nullptr);

  (*data).push_back("123");
  (*data).push_back("abc");

  EXPECT_TRUE(data.has_value());
  EXPECT_TRUE(bool(data));

  EXPECT_EQ(data.data_.get(), &(*data));
  EXPECT_TRUE(data.data_->size() == 2);
  EXPECT_TRUE((*data.data_)[0] == "123");
  EXPECT_TRUE((*data.data_)[1] == "abc");

  data.reset();
  EXPECT_FALSE(data.has_value());
  EXPECT_FALSE(bool(data));
  EXPECT_EQ(data.get(), nullptr);

  (*data).push_back("123");
  (*data).push_back("abc");

  EXPECT_TRUE(data.has_value());
  EXPECT_TRUE(bool(data));

  EXPECT_EQ(data.data_.get(), &(*data));
  EXPECT_TRUE(data.data_->size() == 2);
  EXPECT_TRUE((*data.data_)[0] == "123");
  EXPECT_TRUE((*data.data_)[1] == "abc");
}

}  // namespace test
}  // namespace base
}  // namespace lynx
