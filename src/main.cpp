/**
 * @author humac (hoomaac@gmail.com)
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022 by humac (hoomaac@gmail.com)
 */

#include <iostream>
#include <fstream>
#include <tuple>
#include <memory>

#include "tardis/packfile_manager.h"
#include "tardis/utility/compression.h"

#include "utility/utils.h"


int main(int argc, char const *argv[])
{
    using tardis::PackfileManager;
    using tardis::utils::FileHandle;

    PackfileManager packfile_manager{};

    std::unique_ptr<std::ifstream> stream = FileHandle::input_stream("../file.pack", std::ios::binary);
    
    //packfile_manager.add_files({"../file2.txt", "../file3.txt", "../file4.txt"});
    packfile_manager.add_file("../file2.txt");
    packfile_manager.add_file("../file3.txt");
    packfile_manager.add_file("../file4.txt");

    std::string serialized_buffer = packfile_manager.done();

    return 0;
}
