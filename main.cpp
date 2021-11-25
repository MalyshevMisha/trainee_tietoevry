#include"View.hpp"
#include"NetConfAgent.hpp"

int main()
{
    std::unique_ptr<NetConfAgent> netconf(new NetConfAgent());
    netconf->initSysrepo();
    netconf->subscribeForModelChanges();
    std::string path = "/testmodel:sports/person[name='Mike']/name";
    std::string res;
    netconf->fetchData(path, res);
    std::cout<<res<<std::endl;
    //std::unique_ptr<Interface>inter(new CLI());
    //inter->execute();
    return 0;
}