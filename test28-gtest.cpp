/*
must link gtest and pthread
g++ -o t28-gtest test28-gtest.cpp test28-CBasicMath.cpp -lgtest -lpthread
*/
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <gtest/gtest.h>

#include "test28-CBasicMath.hpp"

using namespace std;

class CBasicMathTest : public ::testing::Test {
//protected: 
public:
  void SetUp() override {
    m_testObj = new CBasicMath();
  }
  void TearDown() override {
    delete m_testObj;
  }
  CBasicMath *m_testObj;
};

TEST(Foo, Int) {
    EXPECT_EQ(123, 123) << "Foo Bar test";
}

TEST_F(CBasicMathTest, Addition) {
    EXPECT_EQ(3+4, m_testObj->Addition(3,4) );
    EXPECT_EQ(0+0, m_testObj->Addition(0,0) ) << "Normal test"; 
    EXPECT_EQ(-1, m_testObj->Addition(-1,0) ) << "Negative value test";
    //ASSERT_EQ(1+0, m_testObj->Addition(-1,0) ) << "Assert test";
}

TEST(Foo, Double) {
    EXPECT_EQ(12.3, 12.3) << "Foo Bar test";
}

TEST_F(CBasicMathTest, Multiply) {
    EXPECT_EQ(3*4, m_testObj->Multiply(3,4) );
    EXPECT_EQ(0, m_testObj->Multiply(0,0) ) << "Normal test"; 
    EXPECT_EQ(0, m_testObj->Multiply(-1,0) ) << "Negative value test";
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

