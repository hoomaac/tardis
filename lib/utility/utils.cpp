#include "tardis/utility/utils.h"


namespace tardis::utils
{

Closable::Closable(std::function<void(int fd)> close_func, int fd)
: m_func{close_func}
, m_fd{fd}
{
}

}  // namespace tardis::utils