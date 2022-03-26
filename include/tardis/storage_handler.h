/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_STORAGE_HANDLER_H_
#define INCLUDE_TARDIS_STORAGE_HANDLER_H_


#include <iostream>
#include <string>
#include <array>


namespace tardis
{

inline bool store(const std::string& buffer, std::ofstream& stream) noexcept
{
    if (!stream.good())
        return false;

    stream.write(buffer.data(), buffer.size());

    return true;
}


}  // namespace tardis

#endif  // INCLUDE_TARDIS_STORAGE_HANDLER_H_
