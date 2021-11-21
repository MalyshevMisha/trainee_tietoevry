#pragma once
#include <sysrepo-cpp/Connection.hpp>

class NetConfAgent
{
private:
    std::unique_ptr<sysrepo::Connection> conn;
    std::unique_ptr<sysrepo::Subscription> sub;
public:
    NetConfAgent(){}
    bool initSysrepo();
    bool closeSysyrepo();
    bool fetchData();
    bool subscribeForModelChanges();
    bool registerOpenData();
    bool subscribeForRpc();
    bool notifySusrepo();
};