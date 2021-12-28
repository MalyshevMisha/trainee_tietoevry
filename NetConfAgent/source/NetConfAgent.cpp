#include"NetConfAgent.hpp"
#include"MobileClient.hpp"

namespace mainApp
{
bool NetConfAgent::initSysrepo()
{
    _conn = std::make_unique<sysrepo::Connection>();
    _sess = _conn->sessionStart();
    return true;
}

bool NetConfAgent::closeSysyrepo(){return false;}

bool NetConfAgent::fetchData(const std::string & path, std::string & result)
{
    auto data = _sess->getData(path.c_str());
    if(data == std::nullopt)
    {
        return false;
    }
    data->path();   
    if(data->findPath(path.c_str()).value().schema().nodeType() == libyang::NodeType::Leaf)
    {
        result = data->findPath(path.c_str()).value().asTerm().valueStr();
        return true;
    }
    return false;
}

bool NetConfAgent::changeData(const std::string & path, const std::string & value)
{
    _sess->setItem(path.c_str(), value.c_str());
    _sess->applyChanges();
    return true;
}

bool NetConfAgent::subscribeForModelChanges(const std::string & modelName, const std::string & path, MobileClient & mobC)
{
    sysrepo::ModuleChangeCb moduleChangeCb = [&] (sysrepo::Session session, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode 
    {
        for (const auto& change : session.getChanges())
            {
                if(change.node.schema().nodeType() == libyang::NodeType::Leaf)
                mobC.handleModuleChange(static_cast<std::string>(change.node.path()),
                                        static_cast<std::string>(change.node.asTerm().valueStr()));
            }
        return sysrepo::ErrorCode::Ok;
    };
    _sub = _sess->onModuleChange(modelName.c_str(), moduleChangeCb, path.c_str(), 0 , sysrepo::SubscribeOptions::DoneOnly, nullptr);
    return true;
}

bool NetConfAgent::removeItem(const std::string & path)
{
    auto data = _sess->getData(path.c_str());
    if(data != std::nullopt)
    {
        _sess->deleteItem(path.c_str());
        _sess->applyChanges();
        return true;
    }
    return false;
}

bool NetConfAgent::registerOperData(const std::string & modelName, const std::string & path, MobileClient & mobC)
{
    sysrepo::OperGetItemsCb operGetCb = [&, path] (sysrepo::Session, auto, auto, auto, auto, auto, std::optional<libyang::DataNode>& parent) 
    {
        parent = _sess->getContext().newPath(path.c_str(), mobC.getName().c_str());
        return sysrepo::ErrorCode::Ok;
    };
    _subOperData = _sess->onOperGetItems(modelName.c_str(), operGetCb, path.c_str());
    std::string res;
    return true;
}

bool NetConfAgent::getOperData(const std::string & path, std::string & result)
{
    _sess->switchDatastore(sysrepo::Datastore::Operational);
    if(fetchData(path, result))
    {
        _sess->switchDatastore(sysrepo::Datastore::Running);
        return true;
    }
    _sess->switchDatastore(sysrepo::Datastore::Running);
    return false;
}

bool NetConfAgent::subscribeForRpc(){return false;}
bool NetConfAgent::notifySusrepo(){return false;}
}