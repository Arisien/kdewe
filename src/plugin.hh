/**
 * @file plugin.hh
 * @author arisien (arisien@vivaldi.net)
 * @brief Definitions for PLugin functions
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef KDEWE_PLUGIN_HH
#define KDEWE_PLUGIN_HH

#include <cstdlib>
#include <string>

#include "files.hh"

namespace Plugin {
    void write_config (std::string entry, std::string value);

    void set_display_mode (int mode);

    void change_wallpaper (std::string steamdir, std::string id);
}

#endif