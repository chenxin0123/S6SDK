
#ifndef S6Plugin_h
#define S6Plugin_h

#include <stdio.h>
#include "S6SDKDefine.h"

S6NAMESPACE_BEGIN

class IPlugin
{
public:
    virtual const char * getName() = 0;
    virtual const char * getVersion() = 0;
};

S6NAMESPACE_END

#endif
