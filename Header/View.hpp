#pragma once
#include<iostream> 
#include<memory>
#include"MobileService.hpp"
#include"Command.hpp"

class Interface
{
public:
    virtual ~Interface() {}
    virtual void execute() = 0;
};

class CLI : public Interface
{
private:
    Command getCommand(); // get command from terminal
    void executeCommand(Command com);   //execute command and print resault
    std::unique_ptr<MobileService> executor;
    bool mainLoop;
public:
    CLI();
    void execute();
};