#pragma once
#include<string>

namespace PathGenerator
{
    const std::string _KEY_WORD("KeyWord");     // the content must be unique for the folowing strings
    const std::string _MODEL_NAME("newCommutator");
    const std::string _NUMBER_PATH = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']/userNumber";
    const std::string _NAME_PATH = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']/userName";
    const std::string _INCOMING_NUMBER_PATH = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']/incomingNamber";
    const std::string _STATE_PATH = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']/state";
    const std::string _PATH_FOR_SUBSCRIBE = "/" + _MODEL_NAME + ":user/subscribers/subscriber[userNumber='" + _KEY_WORD + "']";

    std::string generatePath(const std::string & listId, std::string path);
}

namespace ServState
{
    const std::string _IDLE {"idle"};
    const std::string _ACTIVE {"active"};
    const std::string _BUSY {"busy"};
}