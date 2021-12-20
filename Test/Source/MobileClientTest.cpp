#pragma once
#include<gtest/gtest.h>
#include<gtest/gtest.h>
#include"NetConfAgentMock.hpp"
#include"INetConfAgent.hpp"
#include"MobileClient.hpp"

namespace mock
{

using ::testing::AtLeast;
TEST(FooFighterTest, doSomethingTest)
{
    NetConfAgentMock NCAmock;
    mainApp::MobileClient mobC(std::make_shared<NetConfAgentMock>(NCAmock));
    
    mobC.getName();
}

}

/*int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}*/