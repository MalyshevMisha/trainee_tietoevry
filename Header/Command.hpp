#pragma once
#include<string>
#include<vector>
#include<iostream>

namespace mainApp
{
/**
 * @brief Class Command contain command name and its attributes.
 */
class Command
{
public:
    
    /**
     * @brief Constructor that generate command from input string.
     *
     * @param[in] input String that contains command name and atributes separated by spaces.
     */
    Command(const std::string & input);

    /**
     * @brief Return command name.
     *
     * @return string that means command name.
     */
    std::string getCommandName();

    /**
     * @brief Return vector of command atributes.
     *
     * @return vector of string each string is atributes.
     */
    std::vector<std::string> getAttributes();
    
private:
    std::string commandName;
    std::vector<std::string> attributes;
};
}