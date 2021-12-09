#include"View.hpp"
#include"NetConfAgent.hpp"
#include"MobileClient.hpp"

int main()
{
    std::shared_ptr<MobileClient> mc(new MobileClient);
    std::cout << "set name\t" << mc->setName("Misha") << std::endl;
    std::cout << "regist\t" << mc->regist("2") << std::endl;
    std::cout << "call\t" << mc->call("1") << std::endl;
    //std::string path = "/testmodel:sports/person[name='Mike']";
    //std::string res;
    //std::unique_ptr<NetConfAgent> netC(mc);
    std::unique_ptr<Interface>inter(new CLI);
    inter->execute();
    return 0;
}