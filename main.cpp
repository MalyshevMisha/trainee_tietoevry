#include"View.hpp"
#include"NetConfAgent.hpp"

int main()
{
    std::unique_ptr<NetConfAgent> netconf(new NetConfAgent());
    netconf->initSysrepo();
    netconf->subscribeForModelChanges();
    std::unique_ptr<Interface>inter(new CLI());
    inter->execute();
    return 0;
}