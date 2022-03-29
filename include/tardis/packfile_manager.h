/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_PACKFILE_MANAGER_H_
#define INCLUDE_TARDIS_PACKFILE_MANAGER_H_


#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <tuple>

#include "tardis/packfile.h"
#include "tardis/logger.h"
#include "tardis/storage_handler.h"
#include "tardis/utility/utils.h"
#include "tardis/utility/compression.h"

namespace tardis
{

class PackfileGenerator
{

};

class PackfileManager
{
 public:
    inline PackfileManager() noexcept;

    // TODO(humac): complete this method
    inline internals::Packfile load(const std::string& packfile_path) noexcept;

    inline bool store(const std::string& path) noexcept;

    /**
     * @brief Replaces PackfileManager file paths with new file_paths
     * 
     * @param file_paths List of file paths
     */
    inline void add_files(std::initializer_list<std::string> file_paths) noexcept;

    /**
     * @brief Add a file path to PackfileManager files List
     * 
     * @param file_path Path of a file
     */
    inline void add_file(const std::string& file_path) noexcept;

    inline std::string done() noexcept;

 private:
    /**
     * @brief Prepare file with provided path 
     * 
     * @param file_path File path with will be added to a packfile
     * 
     * @return Returns internals::File 
     */
    internals::File prepare_file(const std::string& file_path) noexcept;

    /**
     * @brief Create a packfile object with already provided file paths 
     * 
     * @return Returns internals::Packfile 
     */
    inline internals::Packfile create_packfile() noexcept;

    /**
     * @brief Serialize the packfile
     * 
     * @param packfile Packfile filled with files
     * 
     * @return Returns serialized string 
     */
    inline std::string serialize(const internals::Packfile& packfile) noexcept;

    /// File paths
    std::vector<std::string> m_file_paths;

    /// Logger instance
    const logger::Log& m_logger;
};

PackfileManager::PackfileManager() noexcept
: m_logger{logger::get_logger(true)}
{
}

internals::Packfile PackfileManager::create_packfile() noexcept
{
    std::vector<internals::File> files;

    for (const std::string& path : m_file_paths)
    {
        if (!utils::is_file_exists(path))
        {
            m_logger.error("file '{}' doesn't exists!", path.c_str());
            continue;
        }

        files.push_back(prepare_file(path));
    }

    internals::Packfile packfile{files};

    return packfile;
}

std::string PackfileManager::serialize(const internals::Packfile& packfile) noexcept
{
    internals::FlatBufferBuilder builder;

    auto flat_packfile = packfile.to_flatbuffer(builder);
    builder.Finish(flat_packfile);

    uint32_t size = builder.GetSize();
    std::string buffer(size, 0);
    std::strncpy(&buffer[0], reinterpret_cast<char*>(builder.GetBufferPointer()), size);
    return buffer;
}

void PackfileManager::add_files(std::initializer_list<std::string> file_paths) noexcept
{
    m_file_paths.assign(file_paths);
}

void PackfileManager::add_file(const std::string& file_path) noexcept
{
    m_file_paths.push_back(file_path);
}

std::string PackfileManager::done() noexcept
{
    internals::Packfile packfile = create_packfile();
    return serialize(packfile);
}


}  // namespace tardis

#endif  // INCLUDE_TARDIS_PACKFILE_MANAGER_H_
