#include <iostream>
#include <fstream>
#include <tuple>

#include "PackfileManager.h"

using namespace std;


int main(int argc, char const *argv[])
{
    using namespace tardis;


    auto packfile = PackfileManager::create({"../file.txt", "../file2.txt"});
    std::string res =  PackfileManager::serialize(packfile);

    PackfileManager::store(res);
    

    return 0;
}
