#include"NetConfAgent.hpp"

bool NetConfAgent::initSysrepo()
{
    _conn = std::make_unique<sysrepo::Connection>();
    _sess = _conn->sessionStart();
    //_sess->copyConfig(sysrepo::Datastore::Startup, "testmodel");
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

bool NetConfAgent::changeNoConfig(const std::string & path, std::string & value)
{
    /*sysrepo::ErrorCode retCode;
    std::optional<libyang::DataNode> toSet;
    sysrepo::OperGetItemsCb operGetCb = [&] (sysrepo::Session, auto, auto, auto, auto, auto, std::optional<libyang::DataNode>& parent)
    {
        parent = toSet;
        return retCode;
    };
    _sub = _sess.onOperGetItems("test_module", operGetCb, "/test_module:stateLeaf");*/
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

bool NetConfAgent::registerOpenData(){return false;}
bool NetConfAgent::subscribeForRpc(){return false;}
bool NetConfAgent::notifySusrepo(){return false;}