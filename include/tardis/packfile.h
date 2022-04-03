/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_PACKFILE_H_
#define INCLUDE_TARDIS_PACKFILE_H_



#include <string>
#include <vector>
#include <tuple>
#include <utility>

#include <libFlatBuf/packfile_generated.h>

#include "tardis/utility/flatbuffers_helper.h"
#include "tardis/logger.h"

namespace tardis::internals
{

// bring some names from flatbuf namespace here
using flatbuf::Convertible;
using flatbuf::FlatBufferType;
using flatbuf::FlatBufferBuilder;

// type aliases
using FlatBufferBlockType = flatbuffers::Offset<flatbuf::Block>;
using FlatBufferFileType = flatbuffers::Offset<flatbuf::File>;


class Block: public Convertible<flatbuf::Block>
{
 public:
    /**
     * @brief Construct a new Block object
     * 
     * @param data Chunk data of a file
     * @param signature Signature of the Block
     * @param block_id Id of the block in a file
     */
    inline Block(std::vector<uint8_t> data, uint32_t signature, uint64_t block_id) noexcept;

    /// @see Converible::to_flatbuffer
    inline FlatBufferType<FlatType> to_flatbuffer(FlatBufferBuilder& builder) const noexcept override;

 private:
    // Fixed-size chuck of a file
    std::vector<uint8_t> m_data;

    // Signature of a block
    uint32_t m_signature;

    // Id of the block inside of a file
    uint64_t m_block_id;
};

class File: public Convertible<flatbuf::File>
{
 public:
    File() = default;

    inline File(std::vector<Block> blocks, const std::string& file_name,
        tardis::flatbuf::FileType file_type) noexcept;

    /// @see Convertible::to_flatbuffer
    inline FlatBufferType<FlatType> to_flatbuffer(FlatBufferBuilder& builder) const noexcept override;

    /**
     * @brief Checks whether file has any blocks
     * 
     * @return True if File is empty, false otherwise
     */
    inline bool is_empty() const noexcept;

    inline void set_block(std::vector<Block>&& blocks) noexcept;
    inline void set_file_name(const std::string& file_name) noexcept;
    inline void set_file_type(flatbuf::FileType file_type) noexcept;

 private:
    // Each file has a number of Blocks
    std::vector<Block> m_blocks;

    // File name
    std::string m_file_name;

    // File type (e.g. Regular, media, ...)
    tardis::flatbuf::FileType m_type;
};

class Packfile: public Convertible<flatbuf::Packfile>
{
 public:
    explicit inline Packfile(const std::vector<File>& files) noexcept;

    inline FlatBufferType<FlatType> to_flatbuffer(FlatBufferBuilder& builder) const noexcept;

 private:
    std::vector<File> m_files;
};

struct BlocksAddr
{
    uint32_t block_id; 
    uint64_t address;
};

Block::Block(std::vector<uint8_t> data, uint32_t signature, uint64_t block_id) noexcept
: m_data{data}
, m_signature{signature}
, m_block_id{block_id}
{
}

FlatBufferType<Block::FlatType> Block::to_flatbuffer(FlatBufferBuilder& builder) const noexcept
{
    auto flat_vector = builder.CreateVector(m_data);
    auto block = flatbuf::CreateBlock(builder, flat_vector, m_signature);

    return block;
}

File::File(std::vector<Block> blocks, const std::string& file_name,
    tardis::flatbuf::FileType file_type) noexcept
: m_blocks{blocks}
, m_file_name{file_name}
, m_type{file_type}
{
}

FlatBufferType<File::FlatType> File::to_flatbuffer(FlatBufferBuilder& builder) const noexcept
{
    std::vector<FlatBufferBlockType> flat_blocks;
    std::for_each(m_blocks.begin(), m_blocks.end(), [&](const Block& block)
    {
        flat_blocks.push_back(block.to_flatbuffer(builder));
    });

    auto flat_string = builder.CreateString(m_file_name);
    auto vectorized_blocks = builder.CreateVector(std::move(flat_blocks));
    auto file = flatbuf::CreateFile(builder, vectorized_blocks, m_type, flat_string);
    return file;
}

bool File::is_empty() const noexcept
{
    return m_blocks.empty();
}

void File::set_block(std::vector<Block>&& blocks) noexcept
{
    m_blocks.clear();
    m_blocks = blocks;
}

void File::set_file_name(const std::string& file_name) noexcept
{
    m_file_name = file_name;
}

void File::set_file_type(flatbuf::FileType file_type) noexcept
{
    m_type = file_type;
}

Packfile::Packfile(const std::vector<File>& files) noexcept
: m_files{files}
{
}

FlatBufferType<Packfile::FlatType> Packfile::to_flatbuffer(FlatBufferBuilder& builder) const noexcept
{
    std::vector<FlatBufferFileType> flat_files;
    std::for_each(m_files.begin(), m_files.end(), [&](const File& file)
    {
        flat_files.push_back(file.to_flatbuffer(builder));
    });

    auto vectorized_files = builder.CreateVector(std::move(flat_files));
    auto packfile = flatbuf::CreatePackfile(builder, vectorized_files);

    return packfile;
}

}  // namespace tardis::internals

#endif  // INCLUDE_TARDIS_PACKFILE_H_
