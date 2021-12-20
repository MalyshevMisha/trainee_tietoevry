#pragma once
#include<gmock/gmock.h>
#include"INetConfAgent.hpp"
#include"NetConfAgent.hpp"
#include"MobileClient.hpp"

class mainApp::INetConfAgent;
class mainApp::NetConfAgent;

namespace mock
{
class NetConfAgentMock : public mainApp::INetConfAgent
{
public:
    MOCK_METHOD0(initSysrepo, bool());
    MOCK_METHOD0(closeSysyrepo, bool());
    MOCK_METHOD2(fetchData, bool(const std::string & path,
                                std::string & result));
    MOCK_METHOD2(changeData, bool(const std::string & path,
                                const std::string & value));
    MOCK_METHOD3(subscribeForModelChanges, bool(const std::string & modelName, 
                                                const std::string & path, 
                                                mainApp::MobileClient & mobC));
    MOCK_METHOD1(removeItem, bool(const std::string & path));
    MOCK_METHOD3(registerOperData, bool(const std::string & modelName, 
                                        const std::string & path, 
                                        mainApp::MobileClient & mobC));
    MOCK_METHOD2(getOperData, bool(const std::string & path,
                                std::string & result));
    MOCK_METHOD0(subscribeForRpc, bool());
    MOCK_METHOD0(notifySusrepo, bool());
};
}