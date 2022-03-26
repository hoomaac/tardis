/**
 * @author humac (hoomaac@gmail.com)
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
 */

#include "tardis/packfile_manager.h"
#include "tardis/signature.h"
#include "tardis/utility/utils.h"
#include "tardis/utility/compression.h"

namespace tardis
{

internals::File PackfileManager::prepare_file(const std::string& file_path) noexcept
{
    using utils::Compression;

    constexpr uint16_t BUFFER_SIZE = 1 << 13;
    const logger::Log& logger = logger::get_logger(true);

    // 8K buffer to read 8K block of a file
    std::string buffer(BUFFER_SIZE, 0);
    std::vector<internals::Block> blocks;
    internals::File file;
    std::ifstream input{file_path};

    Compression compression{};

    if (!input.good())
    {
        logger.error("{} {}", file_path.c_str(), "cannot be opened");
        return file;
    }

    uint64_t count = 0;
    while (input.read(&buffer[0], BUFFER_SIZE))
    {
        uint32_t sign = weak_sig_calculate(buffer);
        std::string z_buffer = compression.compress(buffer);
        internals::Block block{std::vector<uint8_t>(z_buffer.begin(), z_buffer.end()), sign, count};
        blocks.push_back(std::move(block));
        ++count;
    }

    file.set_block(std::move(blocks));
    file.set_file_name(file_path);
    file.set_file_type(flatbuf::FileType::REGULAR);

    return file;
}



}  // namespace tardis
