#include"View.hpp"
#include"NetConfAgent.hpp"

int main()
{
    std::unique_ptr<mainApp::Interface>inter(new mainApp::CLI);
    inter->execute();
    return 0;
}