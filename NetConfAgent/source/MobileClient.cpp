#include"MobileClient.hpp"

namespace mainApp
{
MobileClient::MobileClient(std::shared_ptr<INetConfAgent> netConf)
{
    _netConf = netConf;
    _netConf->initSysrepo();
}

MobileClient::~MobileClient()
{
    if(!_incomingNumber.empty())
    {
        reject();
        callEnd();
    }
    else if(!_outgoingNumber.empty())
    {
        _netConf->changeData(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_STATE_PATH), StateName::_IDLE);
        _netConf->removeItem(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_INCOMING_NUMBER_PATH));
        _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), StateName::_IDLE);
    }
    unregist();
        
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
    _netConf->registerOperData(PathGenerator::_MODEL_NAME,PathGenerator::generatePath(_number, PathGenerator::_NAME_PATH), *this);
    _netConf->subscribeForModelChanges(PathGenerator::_MODEL_NAME, 
                                    PathGenerator::generatePath(number, PathGenerator::_PATH_FOR_SUBSCRIBE), 
                                    *this);
    _netConf->changeData(PathGenerator::generatePath(number, PathGenerator::_STATE_PATH), StateName::_IDLE);
    //_netConf->getOperData(PathGenerator::generatePath(_number, PathGenerator::_NAME_PATH), res); 
    //std::cout << "--regist() getOperData() result\t" << res << "--" << std::endl;
    _state = State::Idle;
    return true;
}

bool MobileClient::unregist()
{
    if(!_number.empty() && _state == State::Idle)
    {
        if(_netConf->removeItem(PathGenerator::generatePath(_number, PathGenerator::_PATH_FOR_SUBSCRIBE)))
        {
            _name.clear();
            _number.clear();
            _incomingNumber.clear();
            _outgoingNumber.clear();
            _state = State::DEFAULT;
            return true;
        }
    }
    return false;
}

bool MobileClient::call(const std::string & number)
{
    std::string res;
    if(number.empty() || _number.empty() ||
     !_incomingNumber.empty() || _number == number ||
     _state != State::Idle)
        return false;
    else if(_netConf->fetchData(PathGenerator::generatePath(number, 
                                PathGenerator::_STATE_PATH), res ))
            {
                if(res == "idle")
                {
                    _outgoingNumber = number;
                
                    _netConf->changeData(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_STATE_PATH), StateName::_ACTIVE);
                    _netConf->changeData(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_INCOMING_NUMBER_PATH), _number);
                    _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), StateName::_ACTIVE);
                    return true;
                }
            }
    return false;
}

void MobileClient::handleModuleChange(std::string path, std::string val)
{
    if(path.find(PathGenerator::_STATE) != std::string::npos && 
        val == StateName::_ACTIVE && _state == State::Idle)
    {
        _state = State::Active;
        std::cout << "--Calling--" << std::endl;
    }
    else if(path.find(PathGenerator::_INCOMING_NUMBER) != std::string::npos &&
            _state == State::Active)
    {
        if(!val.empty())
        {
        _incomingNumber = val;
        std::string res;
        _netConf->getOperData(PathGenerator::generatePath(_incomingNumber, PathGenerator::_NAME_PATH), res); 
        std::cout << "--Incoming call\t" << res << "\t number\t" << val << "--" << std::endl;
        }
    }
    else if(path.find(PathGenerator::_STATE) != std::string::npos && 
        val == StateName::_BUSY && _state == State::Active)
    {
        _state = State::Busy;
        std::cout << "--Connected--" << std::endl;
    }
    else if(path.find(PathGenerator::_STATE) != std::string::npos && 
        val == StateName::_IDLE && _state == State::Busy)
    {
        _state = State::Idle;
        _incomingNumber.clear();
        _outgoingNumber.clear();
        std::cout << "--End call--" << std::endl;
    }
    else if(path.find(PathGenerator::_STATE) != std::string::npos && 
        val == StateName::_IDLE && _state == State::Active)
    {
        _state = State::Idle;
        _incomingNumber.clear();
        _outgoingNumber.clear();
        std::cout << "--Reject--" << std::endl;
    }
    else if(_state == State::Idle && _incomingNumber.empty() &&
            path == PathGenerator::generatePath(_number, PathGenerator::_PATH_FOR_SUBSCRIBE))
    {
        std::cout << "--Unregister--" << std::endl;
    }
}

bool MobileClient::answer()
{
    if(_state == State::Active && !_incomingNumber.empty() && 
        _incomingNumber != _number)
    {
        _netConf->changeData(PathGenerator::generatePath(_incomingNumber, PathGenerator::_STATE_PATH), StateName::_BUSY);
        _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), StateName::_BUSY);
        return true;
    }
    return false;
}

bool MobileClient::callEnd()
{
     if(_state == State::Busy && !_incomingNumber.empty())
    {
        _netConf->changeData(PathGenerator::generatePath(_incomingNumber, PathGenerator::_STATE_PATH), StateName::_IDLE);
        _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_INCOMING_NUMBER_PATH), "");
        _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), StateName::_IDLE);
        return true;
    }
    else if(_state == State::Busy && !_outgoingNumber.empty())
    {
        _netConf->changeData(PathGenerator::generatePath(_outgoingNumber, PathGenerator::_STATE_PATH), StateName::_IDLE);
        _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), StateName::_IDLE);
        return true;
    }
    return false;
}

bool MobileClient::reject()
{
    if(_state == State::Active && !_incomingNumber.empty())
    {
        _netConf->changeData(PathGenerator::generatePath(_incomingNumber, PathGenerator::_STATE_PATH), StateName::_IDLE);
        _netConf->changeData(PathGenerator::generatePath(_number, PathGenerator::_STATE_PATH), StateName::_IDLE);
        _netConf->removeItem(PathGenerator::generatePath(_number, PathGenerator::_INCOMING_NUMBER_PATH));
        return true;
    }
    return false;
}

std::string MobileClient::getName()
{
    return _name;
}
}