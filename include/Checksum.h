#ifndef CHECKSUM_H_
#define CHECKSUM_H_

#include "Rollsum.h"

namespace tardis
{

enum class ChecksumType
{
    WEAK = 0,
    STRONG
};

template<ChecksumType checksumType>
class CheckSum
{
public:

    inline uint32_t calculate(const std::string &buffer) noexcept;

private:

    inline void update(const std::string& buffer) noexcept;

    inline void rotate(u_char in, u_char out) noexcept;

    inline void roll(u_char in) noexcept;

    inline uint32_t digest() noexcept;

    static inline uint32_t mix32(uint32_t h) noexcept;

    RollSum m_rollsum{};    
};

template<ChecksumType checksumType>
void CheckSum<checksumType>::update(const std::string& buffer) noexcept
{
    m_rollsum.update(buffer);
}

template<ChecksumType checksumType>
void CheckSum<checksumType>::rotate(u_char in, u_char out) noexcept
{
    m_rollsum.rotate(in, out);
}

template<ChecksumType checksumType>
void CheckSum<checksumType>::roll(u_char in) noexcept
{
    m_rollsum.roll(in);
}

template<ChecksumType checksumType>
uint32_t CheckSum<checksumType>::digest() noexcept
{
    return mix32(m_rollsum.digest());
}

template<ChecksumType checksumType>
uint32_t CheckSum<checksumType>::mix32(uint32_t h) noexcept
{
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

template<ChecksumType checksumType>
uint32_t CheckSum<checksumType>::calculate(const std::string& buffer) noexcept
{
    //TODO: complete it
    m_rollsum.reset();
    m_rollsum.update(buffer);
    return m_rollsum.digest();
}


using WeakCheckSum = CheckSum<ChecksumType::WEAK>;
using StrongCheckSum = CheckSum<ChecksumType::STRONG>;


}



#endif