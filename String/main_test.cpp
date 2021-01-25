#include <gtest/gtest.h>

#include "myString.h"

TEST(Test_constructors, FIRST) {
  String str1(10000, 'x');
  String str2;
  for (int32_t i = 0; i < 10000; ++i) {
    str2.push_back('y');
  }
  for (int32_t i = 0; i < 10000; ++i) {
    str2.pop_back();
  }
  for (int32_t i = 0; i < 10000; ++i) {
    str2.push_back('x');
  }
  EXPECT_EQ(str1, str2);
}

TEST(Test_substr, FIRST) {
  String str = "strike Strike Strike";
  String str1 = str.substr(5, 10);
  EXPECT_EQ(str1.length(), 10);
}

TEST(Test_istream, FIRST) {
  std::istringstream iss {"my   stream"};

  String str1; // std::string
  iss >> str1;
  EXPECT_EQ(str1.length(), 2);
  EXPECT_EQ(str1, String("my"));

  EXPECT_EQ(iss.tellg(), 5);

  String str2; // std::string
  iss >> str2;
  EXPECT_EQ(str2.length(), 6);
  EXPECT_EQ(str2, String("stream"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}