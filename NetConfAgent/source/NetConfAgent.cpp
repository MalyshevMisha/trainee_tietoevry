#include"NetConfAgent.hpp"

bool NetConfAgent::initSysrepo()
{
    _conn = std::make_unique<sysrepo::Connection>();
    _sess = _conn->sessionStart();
    _sess->copyConfig(sysrepo::Datastore::Startup, "testmodel");
    return true;
}

bool NetConfAgent::closeSysyrepo(){return false;}

bool NetConfAgent::fetchData(const std::string & path, std::string & result)
{
    auto data = _sess->getData(path.c_str());
    data->path();
    result = data->findPath(path.c_str()).value().asTerm().valueStr();
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
        _sess->setItem("/testmodel:sports/person[name='Mike']/age", "12");
        _sess->applyChanges();
    return true;
}

bool NetConfAgent::registerOpenData(){return false;}
bool NetConfAgent::subscribeForRpc(){return false;}
bool NetConfAgent::notifySusrepo(){return false;}