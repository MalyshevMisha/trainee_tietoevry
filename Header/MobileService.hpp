#pragma once 
#include<string>
#include<iostream>

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
    bool regist(const std::string &);
    bool unregist();
    void setName(const std::string &);
    bool call(const std::string &);
    void callEnd();
    void answer();
    void reject();
};
