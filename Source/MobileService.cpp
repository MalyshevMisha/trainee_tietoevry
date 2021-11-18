#include"MobileService.hpp"

    bool TestService::regist(const std::string &)
    {
        std::cout<<"register\n";
        return true;
    }
    bool TestService::unregist()
    {
        std::cout<<"unregister\n";
        return true;
    }
    void TestService::setName(const std::string &)
    {
        std::cout<<"setName\n";
    }
    bool TestService::call(const std::string &)
    {
        std::cout<<"call\n";
        return true;
    }
    void TestService::callEnd()
    {
        std::cout<<"callEnd\n";
    }
    void TestService::answer()
    {
        std::cout<<"answer\n";
    }
    void TestService::reject()
    {
        std::cout<<"reject\n";
    }