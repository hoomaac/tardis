/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#include "tardis/logger.h"

namespace tardis::logger
{

Log::Log(bool log_file) noexcept
{
    // Limit log file size to 8MB
    constexpr uint32_t FILE_LOG_SIZE = 1 << 23;
    constexpr uint8_t MAX_FILE_NUMBER = 2;
    constexpr char TARDIS_PROGRAM[] = "tardis";

    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink;
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> file_sink;

    auto dup_filter = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(DUPLICATE_TIME_OUT));

    if (log_file)
    {
        file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(LOG_PATH, FILE_LOG_SIZE, MAX_FILE_NUMBER);
        file_sink->set_level(spdlog::level::debug);
        dup_filter->add_sink(file_sink);
    }

    console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    dup_filter->add_sink(console_sink);

    spdlog::logger logger(TARDIS_PROGRAM, dup_filter);
    logger.set_level(spdlog::level::debug);
    m_logger = std::make_unique<spdlog::logger>(std::move(logger));
}

}  // namespace tardis::logger
