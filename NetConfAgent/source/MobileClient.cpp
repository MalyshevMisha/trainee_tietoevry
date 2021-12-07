#include"MobileClient.hpp"

MobileClient::MobileClient()
{
    _netConf = std::make_unique<NetConfAgent>(this);
    _netConf->initSysrepo();
}

bool MobileClient::setName(const std::string & name)
{
    if(_name == name || _name.length() == 0)
        return false;
    return true;
}

bool MobileClient::regist(const std::string & number)
{
    std::string res;
    if(_name.empty() || number.empty())
        return false;
    else if(_netConf->fetchData(PathGenerator::generatePath(_number, PathGenerator::_NUMBER_PATH), res ))
        return false;
    _number = number;
    _netConf->subscribeForModelChanges(PathGenerator::_PATH_FOR_SUBSCRIBE);
    _netConf->changeData(PathGenerator::generatePath(number, PathGenerator::_NUMBER_PATH), _number);
    return true;
}

bool MobileClient::unregist()
{
    return false;
}

bool MobileClient::call(const std::string & number)
{
    std::string res;
    if(_name.empty() || number.empty())
        return false;
    else if(!_netConf->fetchData(PathGenerator::generatePath(number, PathGenerator::_NUMBER_PATH), res ))
        return false;
    _incomingNumber = number;
    std::string active {"active"};
    _netConf->changeData(PathGenerator::generatePath(_incomingNumber, PathGenerator::_STATE_PATH), active);
    _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), active);
    return true;
}

void MobileClient::handleModuleChange(const libyang::DataNode & nod)
{
    std::cout<<nod.path()<<std::endl;
    std::cout<<nod.asTerm().valueStr()<<std::endl;
}