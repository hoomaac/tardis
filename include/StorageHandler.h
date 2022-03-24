#ifndef STORAGE_HANDLER_H_
#define STORAGE_HANDLER_H_


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
//TODO: complete NETWORK storage



} // namespace tardis

#endif