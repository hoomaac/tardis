#include "PackfileManager.h"

#include "Signature.h"

#include "Utils.h"

namespace tardis
{



internals::File PackfileManager::prepare_file(const std::string& file_path) noexcept
{
    using namespace std;
    constexpr uint16_t BUFFER_SIZE = 1 << 13;

    const logger::Log& logger = logger::get_logger(true); 

    // 8K buffer to read 8K block of a file
    string buffer(BUFFER_SIZE, 0);
    std::vector<internals::Block> blocks;
    internals::File file;

    ifstream input{file_path};

    if (!input.good())
    {
        logger.error("{} {}", file_path.c_str(), "cannot be opened");
        return file;
    }

    uint64_t count = 0;
    while(input.read(&buffer[0], BUFFER_SIZE))
    {
        uint32_t sign = weak_sig_calculate(buffer);
        internals::Block block{std::vector<uint8_t>(buffer.begin(), buffer.end()), sign, count};
        blocks.push_back(std::move(block));
        ++count;
    }
    
    file.set_block(std::move(blocks));
    file.set_file_name(file_path);
    file.set_file_type(flatbuf::FileType::REGULAR);

    return file;
}



} // namespace tardis