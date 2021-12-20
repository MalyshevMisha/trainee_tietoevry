#pragma once
#include<sysrepo-cpp/Connection.hpp>
#include<iostream>
#include<optional>
#include<atomic>
#include"MobileClient.hpp"
#include"INetConfAgent.hpp"

namespace mainApp
{

/**
 * @brief Class that implements work with server.
 */
class NetConfAgent : public INetConfAgent
{
public:

    /**
     * @brief Initialization to work with sysrepo-cpp.
     *
     * @return /true always, /false otherwise.
     */
    bool initSysrepo();

    /**
     * @brief It does not work.
     *
     * @return /false always.
     */
    bool closeSysyrepo();

    /**
     * @brief Get data from server.
     *
     * @param[in] path Path to the object(item).
     *
     * @param[out] result Returned data.
     *
     * @return /true when get data from server is successful, /false otherwise.
     */
    bool fetchData(const std::string & path,
                    std::string & result);

    /**
     * @brief Change data on server.
     *
     * @param[in] path Path to the object(item).
     *
     * @param[in] value Data for change.
     *
     * @return /true when data was changed, /false otherwise.
     */
    bool changeData(const std::string & path,
                    const std::string & value);

    /**
     * @brief Generate callback that process all of model changes.
     *
     * @param[in] modelName Name of the model subscribe to.
     *
     * @param[in] path Path to the object(item).
     *
     * @param[in] mobC Object that call this method.
     *
     * @return /true when subscribe is successful, /false otherwise.
     */
    bool subscribeForModelChanges(const std::string & modelName, 
                                    const std::string & path, 
                                    MobileClient & mobC);

    /**
     * @brief Remove object(item) on server.
     *
     * @param[in] path Path to the object(item).
     *
     * @return /true when the object(item) is deleted , /false otherwise.
     */
    bool removeItem(const std::string & path);

    /**
     * @brief Generate callback that return operational data(config false).
     *
     * @param[in] modelName Name of the model subscribe to.
     *
     * @param[in] path Path for config false data.
     *
     * @param[in] mobC Object that call this method.
     *
     * @return /true when all is successful, /false otherwise.
     */
    bool registerOperData(const std::string & modelName, 
                        const std::string & path, 
                        MobileClient & mobC);
    
    /**
     * @brief Get operational data(config false).
     *
     * @param[in] path Path for config false data.
     *
     * @param[out] result Data that stored by path.
     *
     * @return /true when get operational data is successful, /false otherwise.
     */
    bool getOperData(const std::string & path, 
                    std::string & result);

    /**
     * @brief It does not work.
     *
     * @return /false always.
     */
    bool subscribeForRpc();

    /**
     * @brief It does not work.
     *
     * @return /false always.
     */
    bool notifySusrepo();

private:
    std::unique_ptr<sysrepo::Connection> _conn;
    std::optional<sysrepo::Session> _sess;
    std::optional<sysrepo::Subscription> _sub;
    std::optional<sysrepo::Subscription> _subOperData;
};
}