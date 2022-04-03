/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_UTILITY_UTILS_H_
#define INCLUDE_TARDIS_UTILITY_UTILS_H_


#include <string>
#include <array>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <functional>
#include <filesystem>
#include <memory>
#include <type_traits>

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

inline bool is_file_exists(const std::string& file_path)
{
    namespace fs = std::filesystem;

    fs::path path{file_path};
    return fs::exists(path);
}

struct Closable
{
    Closable(std::function<void(int fd)> close_func, int fd);
    ~Closable();

    std::function<void(int fd)> m_func;
    int m_fd;
};

}  // namespace tardis::utils


#endif  // INCLUDE_TARDIS_UTILITY_UTILS_H_
