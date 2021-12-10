#pragma once 
#include<string>
#include<iostream>

#include"MobileClient.hpp"

class MobileService
{
public:
    virtual ~MobileService() {}
    virtual bool regist(const std::string &) = 0;
    virtual bool unregist() = 0;
    virtual void setName(const std::string &) = 0;
    virtual bool call(const std::string &) = 0;
    virtual void callEnd() = 0;
    virtual void answer() = 0;
    virtual void reject() = 0;
};

class TestService : public MobileService
{
public:
    bool regist(const std::string & number);
    bool unregist();
    void setName(const std::string & name);
    bool call(const std::string & number);
    void callEnd();
    void answer();
    void reject();
    TestService();
private:
    std::unique_ptr<MobileClient> _mc;
};
