#ifndef PARAMETERREADER_H
#define PARAMETERREADER_H

#include <list>
#include <string>

struct InputParam
{

};

class ParameterReader
{
public:
    static std::list<InputParam> read(std::string fileName);
};

#endif // PARAMETERREADER_H
