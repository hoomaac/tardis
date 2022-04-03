#include "tardis/repository.h"


namespace tardis::internals
{


Repository::Repository(const std::vector<internals::Packfile>& packfiles, const std::vector<internals::Tree> trees)
: m_packfiles{packfiles}
, m_trees{trees}
{
}

}  // namespace tardis::internals