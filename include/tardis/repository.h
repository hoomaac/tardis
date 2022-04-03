#ifndef INCLUDE_TARDIS_REPOSITORY_H_
#define INCLUDE_TARDIS_REPOSITORY_H_


#include <string>
#include <vector>

#include "tardis/packfile.h"
#include "tardis/tree.h"


namespace tardis::internals
{

class Repository
{
 public:
    Repository() = default;
    Repository(const std::vector<internals::Packfile>& packfiles, const std::vector<internals::Tree> trees);

    inline void set_packfiles(const std::vector<internals::Packfile>& packfiles) noexcept;
    inline void set_trees(const std::vector<internals::Tree>& trees) noexcept;

 private:
    std::vector<internals::Packfile> m_packfiles;
    std::vector<internals::Tree> m_trees;

};

void Repository::set_packfiles(const std::vector<internals::Packfile>& packfiles) noexcept
{
    m_packfiles = packfiles;    
}

void Repository::set_trees(const std::vector<internals::Tree>& trees) noexcept
{
    m_trees = trees;
}


}  // namespace tardis::internals



#endif  // INCLUDE_TARDIS_REPOSITORY_H_