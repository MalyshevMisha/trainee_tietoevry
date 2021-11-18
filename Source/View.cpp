#include"View.hpp"
#include<limits>

CLI::CLI()
{
    executor = std::make_unique<TestService>();
    mainLoop = true;
}

Command CLI::getCommand() 
{
    std::string str;
    std::getline(std::cin,str);
    return Command(str);
}

void CLI::executeCommand(Command com)
{
    if(com.getCommandName() == "register")
        executor->regist(com.getAttributes()[0]);
    else if(com.getCommandName() == "unregister")
        executor->unregist();
    else if(com.getCommandName() == "setName")
        executor->setName(com.getAttributes()[0]);
    else if(com.getCommandName() == "call")
        executor->call(com.getAttributes()[0]);
    else if(com.getCommandName() == "callEnd")
        executor->callEnd();
    else if(com.getCommandName() == "answer")
        executor->answer();
    else if(com.getCommandName() == "reject")
        executor->reject();
    else if(com.getCommandName() == "exit")
        mainLoop = false;
    else
        std::cout<<"wrong command\n";
}

void CLI::execute()
{
    while (mainLoop)
    {
        executeCommand(getCommand());
    }
}