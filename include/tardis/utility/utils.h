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

class FileHandle
{
 public:
    inline FileHandle(const std::string& path, std::ios::openmode mode);
    inline FileHandle(std::string&& path, std::ios::openmode mode);

    inline std::unique_ptr<std::ofstream> create_output_stream(std::ios::openmode mode) const;

    inline bool write(const std::string& buffer);

 protected:
    const std::string m_path;
    const std::ios::openmode m_mode;

};

class InputFileHandle: public FileHandle
{
 public:
    inline InputFileHandle(const std::string& path, std::ios::openmode mode);

 private:
    std::unique_ptr<std::ifstream> m_stream;
};

FileHandle::FileHandle(const std::string& path, std::ios::openmode mode)
: m_path{path}
, m_mode{mode}
{
    std::ifstream f{path};
    std::string buffer(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());


}

FileHandle::FileHandle(std::string&& path, std::ios::openmode mode)
: FileHandle{std::move(path), mode}
{
}

InputFileHandle::InputFileHandle(const std::string& path, std::ios::openmode mode)
: FileHandle(path, mode)
, m_stream{std::make_unique<std::ifstream>(m_path, m_mode)}
{
}



}  // namespace tardis::utils


#endif  // INCLUDE_TARDIS_UTILITY_UTILS_H_
