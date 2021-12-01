#pragma once
#include"NetConfAgent.hpp"
#include"MobileState.hpp"
#include"PathGenerator.hpp"

class MobileClient
{
public:
    MobileClient();
    ~MobileClient();

    void handleModuleChange();
    void handleOperData();
    void handleRPC();
    void handleNorification();
    bool regist(const std::string & number);
    bool unregist();
    bool setName(const std::string & name);
    bool call();
    void callEnd();
    void answer();
    void reject();
private:
    std::string _name,
                _number,
                _incomingNumber;
    MobileState _state;
    std::unique_ptr<NetConfAgent> _netConf;
};
