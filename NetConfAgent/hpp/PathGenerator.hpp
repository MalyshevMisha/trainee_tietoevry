#pragma once
#include<string>

namespace mainApp
{
namespace StateName
{
    const std::string _IDLE {"idle"};
    const std::string _ACTIVE {"active"};
    const std::string _BUSY {"busy"};
}

namespace PathGenerator
{
    const std::string _KEY_WORD("KeyWord");     // the content must be unique for the folowing strings
    const std::string _MODEL_NAME("newCommutator");

    const std::string _NUMBER_PATH = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']/userNumber";
    const std::string _NAME_PATH = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']/userName";
    const std::string _INCOMING_NUMBER_PATH = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']/incomingNamber";
    const std::string _STATE_PATH = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']/state";
    const std::string _PATH_FOR_SUBSCRIBE = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']";

    const std::string _USER_NUMBER = "userNumber";
    const std::string _INCOMING_NUMBER = "incomingNamber";
    const std::string _STATE = "state";

    /**
     * @brief Genarate path .
     *
     * @param[in] path Path prototype that mast contain "PATH" in name.
     *  
     * @param[in] listId Client number.
     *
     * @return Path for someone oubject on server.
     */
    std::string generatePath(const std::string & listId, std::string path);
}
}