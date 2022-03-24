#include "Signature.h"
#include "Logger.h"


namespace tardis
{

std::vector<uint32_t> sign_file(const std::string& path)
{
    using namespace std;
    constexpr uint16_t BUFFER_SIZE = 1 << 13;

    logger::Log& logger = logger::get_logger(true);

    // 8K buffer to read 8K block of a file
    string buffer(BUFFER_SIZE, 0);
    std::vector<uint32_t> sum_blocks;

    ifstream file{path};

    ofstream output{"../file.pack", ios::binary | ios::app};

    if (!file.good())
    {
        logger.debug("{} {}", path.c_str(), "cannot be opened");
        return {};
    }

    while(file.read(&buffer[0], BUFFER_SIZE))
    {
        uint32_t sign = weak_sig_calculate(buffer);
        sum_blocks.push_back(std::move(sign));
    }

    return sum_blocks;
}


}