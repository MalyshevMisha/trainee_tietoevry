#pragma once
#include"NetConfAgent.hpp"
#include"MobileState.hpp"
#include"PathGenerator.hpp"

class NetConfAgent;

class MobileClient
{
public:
    MobileClient();

    void handleModuleChange(std::string path, std::string val);
    void handleOperData();
    void handleRPC();
    void handleNorification();
    bool regist(const std::string & number);
    bool unregist();
    bool setName(const std::string & name);
    bool call(const std::string & number);
    void callEnd();
    void answer();
    void reject();
private:
    std::string _name,
                _number,
                _incomingNumber,
                _outgoingNumber;
    std::unique_ptr<NetConfAgent> _netConf;
};