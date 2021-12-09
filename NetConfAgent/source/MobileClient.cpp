#include"MobileClient.hpp"

MobileClient::MobileClient()
{
    _netConf = std::make_unique<NetConfAgent>();
    _netConf->initSysrepo();
}

bool MobileClient::setName(const std::string & name)
{
    if(_name == name || name.empty())
        return false;
    _name = name;
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
    _netConf->changeData(PathGenerator::generatePath(number, PathGenerator::_NUMBER_PATH), _number);
    _netConf->subscribeForModelChanges(PathGenerator::_MODEL_NAME, 
                                    PathGenerator::generatePath(number, PathGenerator::_PATH_FOR_SUBSCRIBE), 
                                    this);
    _netConf->changeData(PathGenerator::generatePath(number, PathGenerator::_STATE_PATH), ServState::_IDLE);
    return true;
}

bool MobileClient::unregist()
{
    return false;
}

bool MobileClient::call(const std::string & number)
{
    std::cout<<"reqest call"<<std::endl;
    std::string res;
    if(number.empty() || _number.empty() ||
     !_incomingNumber.empty() || _number == number)
        return false;
    else if(_netConf->fetchData(PathGenerator::generatePath(number, 
                                PathGenerator::_STATE_PATH), res ))
            {
                std::cout<<"call\t"<<res<<std::endl;
                if(res == "idle")
                {
                    _outgoingNumber = number;
                
                    _netConf->changeData(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_STATE_PATH), ServState::_ACTIVE);
                    _netConf->changeData(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_INCOMING_NUMBER_PATH), _number);
                    _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), ServState::_ACTIVE);
                    return true;
                }
            }
    return false;
}

void MobileClient::handleModuleChange(std::string path, std::string val)
{
    std::cout << "handleModuleChange" << std::endl;
    std::cout<<path<<std::endl;
    std::cout<<val<<std::endl;
}

void MobileClient::answer()
{

}

void MobileClient::callEnd()
{

}

void MobileClient::reject()
{
    /*if(_name.empty() || _number.empty())
    {
        _incomingNumber.clear();
        _outgoingNumber.clear();
    }
    else if()
    
    _netConf->changeData(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_STATE_PATH), active);
    _netConf->changeData(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_INCOMING_NUMBER_PATH), _number);
    _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), active);*/
}