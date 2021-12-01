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
    auto data = _sess->getData(path.c_str()); //null opt
    if(data == std::nullopt)
    {
        return false;
    }
    data->path();
    result = data->findPath(path.c_str()).value().asTerm().valueStr();
    return true;
}

bool NetConfAgent::changeData(const std::string & path, std::string & value)
{
    _sess->setItem(path.c_str(), value.c_str());
    _sess->applyChanges();
    return true;
}

bool NetConfAgent::subscribeForModelChanges()
{
    sysrepo::ModuleChangeCb moduleChangeCb = [] (sysrepo::Session session, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode {
            for (const auto& change : session.getChanges())
                std::cout<<change.node.path()<<std::endl;
            return sysrepo::ErrorCode::Ok;
        };
        _sub = _sess->onModuleChange("testmodel", moduleChangeCb);
        _sub->onModuleChange("testmodel", moduleChangeCb);
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

bool NetConfAgent::registerOpenData(){return false;}
bool NetConfAgent::subscribeForRpc(){return false;}
bool NetConfAgent::notifySusrepo(){return false;}