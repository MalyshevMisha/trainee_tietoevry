#include"View.hpp"
#include"NetConfAgent.hpp"
#include"MobileClient.hpp"

int main()
{
    std::unique_ptr<MobileClient> mc(new MobileClient);
    mc->setName("Misha");
    mc->regist("2");
    mc->call("1");
    //std::string path = "/testmodel:sports/person[name='Mike']";
    //std::string res;
    //std::unique_ptr<NetConfAgent> netC(mc);
    //std::unique_ptr<Interface>inter(new CLI);
    //inter->execute();
    return 0;
}