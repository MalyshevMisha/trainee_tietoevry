#pragma once
#include"INetConfAgent.hpp"
#include"NetConfAgent.hpp"
#include"MobileState.hpp"
#include"PathGenerator.hpp"

namespace mainApp
{
class INetConfAgent;
class NetConfAgent;

/**
 * @brief Class that realize command.
 */
class MobileClient
{
public:

    /**
     * @brief Constructor that initialize encapsulated objects.
     */
    MobileClient();

    /**
     * @brief Distructor that make callEnd, reject and unregister if it is necessary.
     */
    ~MobileClient();

    /**
     * @brief Triggered by callback and responds server changes.
     *
     * @param[in] path Path generated by callback.
     *
     * @param[in] val Value that stored on the server along the path.
     */
    void handleModuleChange(std::string path, std::string val);

    /**
     * @brief It does not work.
     */
    void handleOperData();

    /**
     * @brief It does not work.
     */
    void handleRPC();

    /**
     * @brief It does not work.
     */
    void handleNorification();

    /**
     * @brief Registration of client with a set name and number .
     *
     * @param[in] number Client unique id.
     *
     * @return /true when registration was successful, /false otherwise.
     */
    bool regist(const std::string & number);

    /**
     * @brief Remove client from server if it is necessary.
     *
     * @return /true when remove clients data was successful, /false otherwise.
     */
    bool unregist();

    /**
     * @brief Set client name.
     *
     * @param[in] name Client name.
     *
     * @return /true when the client name was set, /false otherwise.
     */
    bool setName(const std::string & name);

    /**
     * @brief Make a session with another client.
     *
     * @param[in] number Unique id of another client.
     *
     * @return /true when attempt to create a session was successful, /false otherwise.
     */
    bool call(const std::string & number);

    /**
     * @brief End of current call.
     *
     * @return /true when client already registered, /false otherwise.
     */
    bool callEnd();

    /**
     * @brief Creates a session in response to call.
     *
     * @return /true when session was craeted, /false otherwise.
     */
    bool answer();

    /**
     * @brief Refusal to create a session.
     *
     * @return /true when refusal was successful, /false otherwise.
     */
    bool reject();

    /**
     * @brief Return client name.
     *
     * @return Return client name.
     */
    std::string getName();
    

private:
    std::string _name;
    std::string _number;
    std::string _incomingNumber;
    std::string _outgoingNumber;
    State _state;
    std::unique_ptr<INetConfAgent> _netConf;
};
}