#include"MobileService.hpp"

TestService::TestService()
{
    _mc = std::make_unique<MobileClient>();
}

bool TestService::regist(const std::string & number)
{
    std::cout<<"--register--"<<std::endl;
    if(!_mc->regist(number))
        std::cout<<"--unable to register number\t\"" << number << "\"--"<<std::endl;
    return true;
}

bool TestService::unregist()
{
    std::cout<<"--unregister--"<<std::endl;
    if(!_mc->unregist())
        std::cout<<"--unable to unregister number--"<<std::endl;
    return true;
}

void TestService::setName(const std::string & name)
{
    std::cout<<"--setName--"<<std::endl;
    if(!_mc->setName(name))
        std::cout<<"--set name\t\"" << name << "\"\t is impossible--"<<std::endl;
}

bool TestService::call(const std::string &number)
{
    std::cout<<"--call--"<<std::endl;
    if(!_mc->call(number))
        std::cout<<"--cant make call\t\"" << number << "\"--"<<std::endl;
    return true;
}

void TestService::callEnd()
{
    std::cout<<"--callEnd--"<<std::endl;
    _mc->callEnd();
}

void TestService::answer()
{
    std::cout<<"--answer--"<<std::endl;
    _mc->answer();
}

void TestService::reject()
{
    std::cout<<"--reject--"<<std::endl;
    _mc->reject();
}