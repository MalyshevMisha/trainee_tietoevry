#pragma once
#include"NetConfAgent.hpp"
#include"MobileState.hpp"
#include"PathGenerator.hpp"

class NetConfAgent;

enum class State 
{
    DEFAULT,
    Idle,
    Active,
    Busy
};

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
    std::string _name;
    std::string _number;
    std::string _incomingNumber;
    std::string _outgoingNumber;
    State _state;
    std::unique_ptr<NetConfAgent> _netConf;
};