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
    _netConf->changeData(PathGenerator::generatePath(number, PathGenerator::_STATE_PATH), StateName::_IDLE);
    _state = State::Idle;
    return true;
}

bool MobileClient::unregist()
{
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
    std::cout << "\n--path == PathGenerator::_STATE_PATH\t" << (path.find(PathGenerator::_STATE) != std::string::npos) << "--\n";
    std::cout << "\n--path == PathGenerator::_INCOMING_NUMBER_PATH\t" << (path.find(PathGenerator::_INCOMING_NUMBER) != std::string::npos) << "--\n" << std::endl;

    /*std::cout << "\n--val == StateName::_ACTIVE\t" << (val == StateName::_ACTIVE) << "--\n";
    std::cout << "\n--val == StateName::_IDLE\t" << (val == StateName::_IDLE) << "--\n";
    std::cout << "\n--val == StateName::_BUSY\t" << (val == StateName::_BUSY) << "--\n" << std::endl;

    std::cout << "\n--_state == State::Idle\t" << (_state == State::Idle) << "--\n";
    std::cout << "\n--_state == State::Active\t" << (_state == State::Active) << "--\n";
    std::cout << "\n--_state == State::Busy\t" << (_state == State::Busy) << "--\n" << std::endl;

    std::cout << "\n--_state == State::Busy\t" << (_state == State::Busy) << "--\n" << std::endl;*/

    //std::cout << "\n--!_outgoingNumber.empty()\t" << (!_outgoingNumber.empty()) << "--\n" << std::endl;



    if(path.find(PathGenerator::_STATE) != std::string::npos && 
        val == StateName::_ACTIVE)
    {
        std::cout << "\n--Calling--\n" << std::endl;
    }
    else if(path.find(PathGenerator::_INCOMING_NUMBER) != std::string::npos)
    {
        _incomingNumber = val;
        std::cout << "\n--Incoming call\t" << val << "--\n" << std::endl;
    }
    else if(path.find(PathGenerator::_STATE) != std::string::npos && 
        val == StateName::_BUSY)
    {
        std::cout << "\n--Connected--\n" << std::endl;
    }
    else if(path.find(PathGenerator::_STATE) != std::string::npos && 
        val == StateName::_IDLE)
    {
        _incomingNumber.clear();
        _outgoingNumber.clear();
        std::cout << "\n--End call--\n" << std::endl;
    }
    else
    {
        std::cout << "\n--Something went wrong--\n" << std::endl;
    }
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