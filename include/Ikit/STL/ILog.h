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

    template <typename T>
    void _ILog(T m)
    {
        std::cout << m << std::endl;
    }

    template <typename T, typename... Args>
    void _ILog(T m, const Args &...msgs)
    {
        std::cout << m;
        _ILog(msgs...);
    }

    template <typename... Args>
    void ILog(DebugLogLevel console, DebugLogLevel base, const Args &...msgs)
    {
        if (console <= base)
            _ILog(msgs...);
    }

} // namespace KTKR
