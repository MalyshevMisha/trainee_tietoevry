#pragma once
#include<sysrepo-cpp/Connection.hpp>
#include<iostream>
#include<optional>
#include<atomic>
#include"MobileClient.hpp"

class MobileClient;

class NetConfAgent
{
public:
    NetConfAgent(MobileClient * mobC);
    bool initSysrepo();
    bool closeSysyrepo();
    bool fetchData(const std::string & path,
                     std::string & result);
    bool changeData(const std::string & path,
                     std::string & value);
    bool changeNoConfig(const std::string & path,
                         std::string & value);
    bool subscribeForModelChanges(const std::string & path);
    bool registerOpenData();
    bool subscribeForRpc();
    bool notifySusrepo();

private:
    std::unique_ptr<sysrepo::Connection> _conn;
    std::optional<sysrepo::Session> _sess;
    std::optional<sysrepo::Subscription> _sub;
    MobileClient * _observ;
};