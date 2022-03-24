#ifndef PACKFILE_MANAGER_H_
#define PACKFILE_MANAGER_H_

#include <fstream>
#include <tuple>

#include "Packfile.h"
#include "Logger.h"

#include "StorageHandler.h"
#include "Utils.h"

namespace tardis
{

class PackfileManager
{
public:


    inline PackfileManager() noexcept;

    static inline internals::Packfile create(const std::vector<std::string>& file_paths) noexcept;

    static inline std::string serialize(const internals::Packfile& packfile) noexcept;

    static inline void store(const std::string& buffer) noexcept;

    inline internals::Packfile& add_packfile() noexcept;

private:


    static internals::File prepare_file(const std::string& file_path) noexcept;

};

internals::Packfile PackfileManager::create(const std::vector<std::string>& file_paths)  noexcept
{
    std::vector<internals::File> files;

    for(const auto& path: file_paths)
        files.push_back(prepare_file(path));
    
    internals::Packfile packfile{files, "../file.pack"};

    return std::move(packfile);
}

std::string PackfileManager::serialize(const internals::Packfile& packfile) noexcept
{
    internals::FlatBufferBuilder builder;
    std::vector<char> tmp{};

    auto flat_packfile = packfile.to_flatbuffer(builder);
    builder.Finish(flat_packfile);

    uint32_t size = builder.GetSize();
    std::string buffer(size, 0);
    std::strncpy(&buffer[0], reinterpret_cast<char*>(builder.GetBufferPointer()), size);
    return buffer;
}

void PackfileManager::store(const std::string& buffer) noexcept
{
    std::ofstream output{"../file.pack"};
    output << buffer;
    output.close();
}

} // namespace tardis

#endif