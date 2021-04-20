#pragma once
#include <iostream>

namespace KTKR
{
    enum DebugLogLevel
    {
        LOG_TRACE = 0,
        LOG_DEBUG,
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR
    };

    void ILog(const char *msg, DebugLogLevel console, DebugLogLevel base)
    {
        if (console <= base)
            std::cout << msg;
    }

} // namespace KTKR
