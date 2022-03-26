/**
 * @author humac (hoomaac@gmail.com)
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
 */

#include "tardis/rollsum.h"

namespace tardis
{

void RollSum::update(const std::string& buffer) noexcept
{
    uint32_t t_s1 = s1;
    uint32_t t_s2 = s2;
    size_t len = buffer.size();

    for (size_t i = 0; i < len; i++)
    {
        t_s1 += buffer[i];
        t_s2 += t_s1;
    }

    t_s1 += len * CHAR_OFFSET;
    t_s2 += ((len * (len + 1)) / 2) * CHAR_OFFSET;
    count_bytes += len;
    s1 = t_s1;
    s2 = t_s2;
}

}  // namespace tardis
