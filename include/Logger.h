#ifndef LOGGER_H_
#define LOGGER_H_

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>

namespace tardis::logger
{

constexpr uint64_t DUPLICATE_TIME_OUT = 5;

class Log
{

public:

    inline Log(bool log_file);

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

Log::Log(bool log_file)
{
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink;
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> file_sink;

    auto dup_filter = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(DUPLICATE_TIME_OUT));

    if (log_file)
    {
        file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("../tardis.log", 1024 * 1024 * 8, 2);
        file_sink->set_level(spdlog::level::debug);
        dup_filter->add_sink(file_sink);
    }
    
    console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    dup_filter->add_sink(console_sink);

    spdlog::logger logger("tardis", dup_filter);
    logger.set_level(spdlog::level::debug);
    m_logger = std::make_unique<spdlog::logger>(std::move(logger));
}

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

}

#endif