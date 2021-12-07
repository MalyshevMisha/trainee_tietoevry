#include"PathGenerator.hpp"

std::string PathGenerator::generatePath(const std::string & listId, std::string path)
{
    return path.replace(path.find(PathGenerator::_KEY_WORD),
                         PathGenerator::_KEY_WORD.length(),
                          listId);
}