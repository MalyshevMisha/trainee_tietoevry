#include"Command.hpp"

Command::Command(const std::string & str)
{
    unsigned int spaceCounter = 0;
    for(auto i : str)
    {
        if(i == ' ')
        {
            ++spaceCounter;
        }
        else
        {
            if(!spaceCounter)   
            {
                commandName += i;
            }
            else
            {
                if (attributes.size() < spaceCounter)
                    attributes.push_back(std::string());
                attributes[spaceCounter-1] += i;
            }
        }
    }
}

std::string Command::getCommandName()
{
    return commandName;
}

std::vector<std::string> Command::getAttributes()
{
    return attributes;
}