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
    if(com.getCommandName() == "register" && com.getAttributes().size() == 1)
        executor->regist(com.getAttributes()[0]);
    else if(com.getCommandName() == "unregister" && com.getAttributes().size() == 0)
        executor->unregist();
    else if(com.getCommandName() == "setName" && com.getAttributes().size() == 1)
        executor->setName(com.getAttributes()[0]);
    else if(com.getCommandName() == "call" && com.getAttributes().size() == 1)
        executor->call(com.getAttributes()[0]);
    else if(com.getCommandName() == "callEnd" && com.getAttributes().size() == 0)
        executor->callEnd();
    else if(com.getCommandName() == "answer" && com.getAttributes().size() == 0)
        executor->answer();
    else if(com.getCommandName() == "reject" && com.getAttributes().size() == 0)
        executor->reject();
    else if(com.getCommandName() == "exit" && com.getAttributes().size() == 0)
        mainLoop = false;
    else
        std::cout<<"wrong command" << std::endl;
}

void CLI::execute()
{
    while (mainLoop)
    {
        executeCommand(getCommand());
    }
}