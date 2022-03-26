/**
 * @author humac (hoomaac@gmail.com)
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
 */

#include "tardis/signature.h"
#include "tardis/logger.h"


namespace tardis
{

std::vector<uint32_t> sign_file(const std::string& path)
{
    constexpr uint16_t BUFFER_SIZE = 1 << 13;

    logger::Log& logger = logger::get_logger(true);

    // 8K buffer to read 8K block of a file
    std::string buffer(BUFFER_SIZE, 0);
    std::vector<uint32_t> sum_blocks{};

    std::ifstream file{path};

    if (!file.good())
    {
        logger.debug("{} {}", path.c_str(), "cannot be opened");
        return {};
    }

    while (file.read(&buffer[0], BUFFER_SIZE))
    {
        uint32_t sign = weak_sig_calculate(buffer);
        sum_blocks.push_back(std::move(sign));
    }

    return sum_blocks;
}

}  // namespace tardis
