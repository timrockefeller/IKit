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

    template <class... Args>
    void ILog(DebugLogLevel console, DebugLogLevel base, const char *fmt, const Args &...args)
    {
        std::string buffer;
        sprintf_s(buffer, fmt, std::forward(args));
        if (console <= base)
            std::cout << fmt;
    }

} // namespace KTKR
