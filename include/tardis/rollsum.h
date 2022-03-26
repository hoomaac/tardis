/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_ROLLSUM_H_
#define INCLUDE_TARDIS_ROLLSUM_H_


#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


namespace tardis
{

class RollSum
{
 public:
    inline RollSum() noexcept;

    /// @brief brief description
    inline void reset() noexcept;

    /**
     * @brief 
     * 
     * @param in 
     * @param out 
     */
    inline void rotate(u_char in, u_char out) noexcept;

    inline void roll(u_char in) noexcept;

    /// @brief brief description
    inline uint32_t digest() noexcept;

    void update(const std::string& buffer) noexcept;

 private:
    static constexpr uint8_t CHAR_OFFSET = 31;

    uint32_t s1;
    uint32_t s2;
    size_t count_bytes;
};

RollSum::RollSum() noexcept
: s1{0}
, s2{0}
, count_bytes{0}
{
}

inline void RollSum::reset() noexcept
{
    s1 = 0;
    s2 = 0;
    count_bytes = 0;
}

inline void RollSum::rotate(u_char in, u_char out) noexcept
{
    s1 += in - out;
    s2 += s1 - count_bytes * (out + CHAR_OFFSET);
}

inline void RollSum::roll(u_char in) noexcept
{
    s1 += in + CHAR_OFFSET;
    s2 += s1;
    ++count_bytes;
}

inline uint32_t RollSum::digest() noexcept
{
    return (s2 << 16) | (s1 & 0xffff);
}

}  // namespace tardis


#endif  // INCLUDE_TARDIS_ROLLSUM_H_
