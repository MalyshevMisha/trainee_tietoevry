#pragma once 
#include<string>
#include<iostream>

#include"MobileClient.hpp"

namespace mainApp
{
/**
 * @brief Interface that discribe command.
 */
class IMobileService
{
public:

    /**
     * @brief Virtual distructor created ot escape memory leak.
     */
    virtual ~IMobileService() = default;

    /**
     * @brief Print register status.
     *
     * @param[in] number Its unque client id .
     *
     * @return /true when client already registered, /false otherwise.
     */
    virtual bool regist(const std::string & number) = 0;
 
    /**
     * @brief Print unregister status.
     *
     * @return /true when client already unregistered, /false otherwise.
     */
    virtual bool unregist() = 0;

    /**
     * @brief Print setName status.
     *
     * @param[in] name Cliet name.
     *
     * @return /true when setting name was successful, /false otherwise.
     */
    virtual bool setName(const std::string & name) = 0;

    /**
     * @brief Print status when you try to call.
     *
     * @param[in] number Number of another client.
     *
     * @return /true when call was successful, /false otherwise.
     */
    virtual bool call(const std::string & number) = 0;

    /**
     * @brief Print status of callEnd.
     *
     * @return /true when end of call was successful, /false otherwise.
     */
    virtual bool callEnd() = 0;

    /**
     * @brief Print answer status.
     *
     * @return /true when answer was successful, /false otherwise.
     */
    virtual bool answer() = 0;

    /**
     * @brief Print reject status.
     *
     * @return /true when reject was successful, /false otherwise.
     */
    virtual bool reject() = 0;
};

/**
 * @brief Class that run commands.
 */
class TestService : public IMobileService
{
public:

    /**
     * @brief Class that run commands.
     */
    TestService();
    
    /**
     * @brief Print register status.
     *
     * @param[in] number Its unque client id .
     *
     * @return /true when client already registered, /false otherwise.
     */
    bool regist(const std::string & number);

    /**
     * @brief Print unregister status.
     *
     * @return /true when client already unregistered, /false otherwise.
     */
    bool unregist();

    /**
     * @brief Print setName status.
     *
     * @param[in] name Cliet name.
     *
     * @return /true when setting name was successful, /false otherwise.
     */
    bool setName(const std::string & name);

    /**
     * @brief Print status when you try to call.
     *
     * @param[in] number Number of another client.
     *
     * @return /true when call was successful, /false otherwise.
     */
    bool call(const std::string & number);

    /**
     * @brief Print status of callEnd.
     *
     * @return /true when end of call was successful, /false otherwise.
     */
    bool callEnd();

    /**
     * @brief Print answer status.
     *
     * @return /true when answer was successful, /false otherwise.
     */
    bool answer();

    /**
     * @brief Print reject status.
     *
     * @return /true when reject was successful, /false otherwise.
     */
    bool reject();

private:
    std::unique_ptr<MobileClient> _mc;
};
}