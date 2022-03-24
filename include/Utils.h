#ifndef UTILS_H_
#define UTILS_H_


#include <string>
#include <array>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <functional>

namespace tardis::utils
{


template<typename T, size_t N>
inline std::array<T, N>& to_array(T&& buffer)
{
    std::array<T, N> arr;
    std::copy_n(std::begin(buffer), N, arr.begin());
    std::ifstream stream{};
    
    return arr;
}

template<size_t N>
inline std::array<uint8_t, N>& to_array(uint8_t&& buffer)
{
    return to_array<N>(buffer);
}

struct FileHandler
{
    inline FileHandler(const std::string& path) noexcept;
    inline ~FileHandler() noexcept;

    inline std::fstream& operator()() noexcept;

    std::fstream stream;
};

FileHandler::FileHandler(const std::string& path) noexcept
: stream{path}
{
}

FileHandler::~FileHandler() noexcept
{
    if (stream.is_open())
        stream.close();
}

std::fstream& FileHandler::operator()() noexcept
{
    return stream;
}

}



#endif