#include"PathGenerator.hpp"

std::string generatePathNumber(const std::string & number)
{
    return std::string("/"+PathGenerator::_MODEL_NAME + ":" + "user" + 
    "/" + "subscribers" +  "/" + "subscriber" + 
    "[userNumber='" + number + "']" + "/" + "userNumber");
}

std::string generatePathName(const std::string & number)
{
    return std::string("/"+PathGenerator::_MODEL_NAME + ":" + "user" + 
    "/" + "subscribers" +  "/" + "subscriber" + 
    "[userNumber='" + number + "']" + "/" + "userName");}