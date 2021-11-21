#include"NetConfAgent.hpp"

bool NetConfAgent::initSysrepo()
{
    conn = std::make_unique<sysrepo::Connection>();
    return true;
}

bool NetConfAgent::closeSysyrepo(){return false;}
bool NetConfAgent::fetchData(){return false;}

bool NetConfAgent::subscribeForModelChanges()
{
    auto sess = conn->sessionStart();
    sess.copyConfig(sysrepo::Datastore::Startup, "testmodel");
    int called = 0;
    sysrepo::ModuleChangeCb moduleChangeCb = [&called] (auto, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode {
            called++;
            return sysrepo::ErrorCode::Ok;
        };
        (*sub) = sess.onModuleChange("testmodel", moduleChangeCb);
    return true;
}

bool NetConfAgent::registerOpenData(){return false;}
bool NetConfAgent::subscribeForRpc(){return false;}
bool NetConfAgent::notifySusrepo(){return false;}