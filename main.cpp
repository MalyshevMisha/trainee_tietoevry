#include"View.hpp"
#include"NetConfAgent.hpp"

int main()
{
    std::unique_ptr<Interface>inter(new CLI);
    inter->execute();
    return 0;
}