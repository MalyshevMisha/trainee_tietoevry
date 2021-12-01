#include"View.hpp"
#include"NetConfAgent.hpp"

int main()
{
    std::unique_ptr<NetConfAgent> netconf(new NetConfAgent());
    netconf->initSysrepo();
    netconf->subscribeForModelChanges();
    std::string path = "/testmodel:sports/person[name='Mike']";
    std::string res;
    std::string age{"12"};
    //netconf->changeData(path+"/age", age);
    netconf->fetchData(path+"/age", res);
    std::cout<<res<<std::endl;
    //std::unique_ptr<Interface>inter(new CLI());
    //inter->execute();
    return 0;
}