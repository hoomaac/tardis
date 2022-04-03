#ifndef INCLUDE_TARDIS_TREE_H_
#define INCLUDE_TARDIS_TREE_H_


#include <string>


namespace tardis::internals
{

class Tree
{
 public:
    Tree() = default;
    Tree(const std::string& path, const std::string& hash);

 private:
    std::string m_path;
    std::string m_hash;
    bool m_is_subtree;
};



}  // namespace tardis::internals



#endif  // INCLUDE_TARDIS_TREE_H_