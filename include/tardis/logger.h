/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_LOGGER_H_
#define INCLUDE_TARDIS_LOGGER_H_

#include <memory>
#include <utility>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>

#include "config/config.h"

namespace tardis::logger
{

constexpr uint64_t DUPLICATE_TIME_OUT = 5;

class Log
{
 public:
    explicit Log(bool log_file) noexcept;

    template<typename ...Args>
    inline void info(const std::string format, Args&& ...args) const noexcept;

    template<typename ...Args>
    inline void debug(const char* format, const Args& ...args) const noexcept;

    template<typename ...Args>
    inline void error(const char* format, const Args& ...args) const noexcept;

    template<typename ...Args>
    inline void warn(const char* format, const Args& ...args) const noexcept;

 private:
    std::unique_ptr<spdlog::logger> m_logger;
};

template<typename ...Args>
void Log::info(const std::string format, Args&& ...args) const noexcept
{
    m_logger->info(format, args...);
}

template<typename ...Args>
void Log::debug(const char* format, const Args& ...args) const noexcept
{
    m_logger->debug(format, args...);
}

template<typename ...Args>
void Log::error(const char* format, const Args& ...args) const noexcept
{
    m_logger->error(format, args...);
}

template<typename ...Args>
void Log::warn(const char* format, const Args& ...args) const noexcept
{
    m_logger->warn(format, args...);
}

inline Log& get_logger(bool log_file)
{
    static Log log{log_file};
    return log;
}

}  // namespace tardis::logger

#endif  // INCLUDE_TARDIS_LOGGER_H_
