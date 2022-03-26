/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_UTILITY_COMPRESSION_H_
#define INCLUDE_TARDIS_UTILITY_COMPRESSION_H_


#include <zstd.h>

#include <memory>
#include <string>

namespace tardis::utils
{

// Compress a buffer using zstd library (zstandard), by calling compress method and pass a buffer to it.
// Zstd compression works with a compression level and it's set to 22 as it is.
class Compression
{
 public:
    inline Compression() noexcept;

    inline ~Compression() noexcept;

    /**
     * @brief Compress a buffer using zstd compression
     * 
     * @param buffer Input buffer
     * 
     * @return Returns compressed string
     */
    inline std::string compress(const std::string& buffer) const noexcept;

 private:
    // Compress level of zstd compression
    static constexpr uint8_t COMPRESSION_LEVEL = 22;

    // keep zstd context alive during multiple compression
    ZSTD_CCtx* m_contex;
};

Compression::Compression() noexcept
: m_contex{ZSTD_createCCtx()}
{
}

Compression::~Compression() noexcept
{
    if (m_contex)
        ZSTD_freeCCtx(m_contex);
}

std::string Compression::compress(const std::string& buffer) const noexcept
{
    std::string z_buffer{};
    size_t estimated_size = ZSTD_compressBound(buffer.size());

    z_buffer.resize(estimated_size);
    size_t size = ZSTD_compressCCtx(m_contex, z_buffer.data(), z_buffer.size(), buffer.data(),
        buffer.size(), COMPRESSION_LEVEL);

    // resize to avoid wasting space
    z_buffer.resize(size);
    z_buffer.shrink_to_fit();

    return z_buffer;
}

}  // namespace tardis::utils


#endif  // INCLUDE_TARDIS_UTILITY_COMPRESSION_H_
