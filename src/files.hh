/**
 * @file files.hh
 * @author arisien (arisien@vivaldi.net)
 * @brief Function definitions for File management
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef KDEWE_FILES_HH
#define KDEWE_FILES_HH

#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <string>

namespace Files {
    std::string homedir ();

    bool accesible (std::string path);

    std::string read (std::string path);

    void write (std::string path, std::string src);
}

#endif