#pragma once
#include<gmock/gmock.h>
#include"INetConfAgent.hpp"
#include"NetConfAgent.hpp"

class mainApp::INetConfAgent;
class mainApp::NetConfAgent;

class NetConfAgentMock : public mainApp::INetConfAgent
{
public:
    MOCK_METHOD0(initSysrepo, bool());
    //MOCK_METHOD1(bool, removeItem, (const std::string & path), (override));
};