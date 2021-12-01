#include"MobileClient.hpp"

MobileClient::MobileClient()
{
    _netConf = std::make_unique<NetConfAgent>();
}

bool MobileClient::setName(const std::string & name)
{
    std::string res;
    if(name.empty())
        return false;
    else if(!_netConf->fetchData(PathGenerator::generatePathNumber(_number),
        res ))
        return false;
    _name = name;
    _netConf->changeData(PathGenerator::generatePathName(_number), _name);
    return true;
}

bool MobileClient::regist(const std::string & number)
{
    std::string res;
    if(number.empty())
        return false;
    else if(_netConf->fetchData(PathGenerator::generatePathNumber(_number),
        res ))
        return false;
    _number = number;
    _netConf->changeData(PathGenerator::generatePathNumber(_number), _number);
    return true;
}

bool MobileClient::unregist()
{
    return false;
}

bool MobileClient::call()
{
    return false;
}