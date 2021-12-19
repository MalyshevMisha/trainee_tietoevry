#pragma once
#include<iostream> 
#include<memory>
#include"MobileService.hpp"
#include"Command.hpp"

namespace mainApp
{

/**
 * @brief Interface that discribe user interface.
 */
class Interface
{
public:

    /**
     * @brief Virtual distructor created ot escape memory leak.
     */
    virtual ~Interface() = default;

    /**
     * @brief Run loop for entering commands.
     */
    virtual void execute() = 0;
};


/**
 * @brief Realization of command line user interface.
 */
class CLI : public Interface
{
public:

    /**
     * @brief Constructor of CLI class.
     */
    CLI();

    /**
     * @brief Run loop for entering commands.
     */
    void execute();
private:

    /**
     * @brief Get command from terminal.
     *
     * @return ADT that contains command name and atributes.
     */
    Command getCommand();

    /**
     * @brief Get command from ADT and run it.
     *
     * @param[in] com ADT that contains command name and atributes.
     */
    void executeCommand(Command com);

    std::unique_ptr<IMobileService> executor;
    bool mainLoop;

};
}