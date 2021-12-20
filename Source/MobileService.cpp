#include"MobileService.hpp"

namespace mainApp
{
TestService::TestService()
{
    _mc = std::make_unique<MobileClient>(std::make_shared<NetConfAgent>());
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

bool TestService::setName(const std::string & name)
{
    std::cout<<"--setName--"<<std::endl;
    if(!_mc->setName(name))
    {
        std::cout<<"--set name\t\"" << name << "\"\t is impossible--"<<std::endl;
        return false;
    }
    return true;
}

bool TestService::call(const std::string & number)
{
    std::cout<<"--call--"<<std::endl;
    if(!_mc->call(number))
        std::cout<<"--impossible to make call\t\"" << number << "\"--"<<std::endl;
    return true;
}

bool TestService::callEnd()
{
    if(_mc->callEnd())
    {
        std::cout<<"--callEnd--"<<std::endl;
        return true;
    }
    std::cout<<"--impossible to make callEnd--"<<std::endl;
    return false;
}

bool TestService::answer()
{
    if(_mc->answer())
    {
        std::cout<<"--answer--"<<std::endl;
        return true;
    }
    std::cout<<"--impossible to make answer--"<<std::endl;
    return false;
}

bool TestService::reject()
{
    if(_mc->reject())
    {
        std::cout<<"--reject--"<<std::endl;
        return true;
    }
    std::cout<<"--impossible to make reject--"<<std::endl;
    return false;
}
}