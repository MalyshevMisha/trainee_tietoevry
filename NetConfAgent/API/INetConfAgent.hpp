#pragma once
#include"MobileClient.hpp"
#include"INetConfAgent.hpp"
#include<string>

namespace mainApp
{
class MobileClient;

class INetConfAgent
{
public:
    virtual ~INetConfAgent() = default;

    /**
     * @brief Initialization to work with sysrepo-cpp.
     *
     * @return /true always, /false otherwise.
     */
    virtual bool initSysrepo() = 0;

    /**
     * @brief It does not work.
     *
     * @return /false always.
     */
    virtual bool closeSysyrepo() = 0;

    /**
     * @brief Get data from server.
     *
     * @param[in] path Path to the object(item).
     *
     * @param[out] result Returned data.
     *
     * @return /true when get data from server is successful, /false otherwise.
     */
    virtual bool fetchData(const std::string & path,
                            std::string & result) = 0;

    /**
     * @brief Change data on server.
     *
     * @param[in] path Path to the object(item).
     *
     * @param[in] value Data for change.
     *
     * @return /true when data was changed, /false otherwise.
     */
    virtual bool changeData(const std::string & path,
                            const std::string & value) = 0;

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
    virtual bool subscribeForModelChanges(const std::string & modelName, 
                                            const std::string & path, 
                                            MobileClient & mobC) = 0;

    /**
     * @brief Remove object(item) on server.
     *
     * @param[in] path Path to the object(item).
     *
     * @return /true when the object(item) is deleted , /false otherwise.
     */
    virtual bool removeItem(const std::string & path) = 0;

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
    virtual bool registerOperData(const std::string & modelName, 
                                    const std::string & path, 
                                    MobileClient & mobC) = 0;
    
    /**
     * @brief Get operational data(config false).
     *
     * @param[in] path Path for config false data.
     *
     * @param[out] result Data that stored by path.
     *
     * @return /true when get operational data is successful, /false otherwise.
     */
    virtual bool getOperData(const std::string & path, 
                            std::string & result) = 0;

    /**
     * @brief It does not work.
     *
     * @return /false always.
     */
    virtual bool subscribeForRpc() = 0;

    /**
     * @brief It does not work.
     *
     * @return /false always.
     */
    virtual bool notifySusrepo() = 0;
};
}