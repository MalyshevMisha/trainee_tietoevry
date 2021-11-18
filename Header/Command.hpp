#pragma once
#include<string>
#include<vector>

class Command
{
private:
std::string commandName;
std::vector<std::string> attributes;
public:
    Command(const std::string &);
    std::string getCommandName();
    std::vector<std::string> getAttributes();
};
