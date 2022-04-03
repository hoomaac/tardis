#ifndef INCLUDE_TARDIS_META_H_
#define INCLUDE_TARDIS_META_H_


#include <string>
#include <unordered_map>

#include "tardis/packfile.h"

namespace tardis::internals
{

class Meta
{
 public:
    Meta() = default;
    Meta(const std::unordered_map<std::string, BlocksAddr>& blocks_map);

    inline bool add(const std::pair<std::string, BlocksAddr>& blocks_pair);

    const BlocksAddr& find(const std::string& file_hash) const;

    bool exists(const std::string& file_hash) const noexcept;

 private:
    std::unordered_map<std::string, BlocksAddr> m_blocks_map;
};


}  // namespace tardis::internals


#endif  // INCLUDE_TARDIS_META_H_