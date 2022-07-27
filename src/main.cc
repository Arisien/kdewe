/**
 * @file main.cc
 * @author arisien (arisien@vivaldi.net)
 * @brief Entry point for KDEWE
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "./json/jsonvalue.cc"
#include "./json/json.cc"

#include "files.cc"
#include "plugin.cc"

#include <iostream>

int main (int argc, char** argv) {

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [wallpaper id]" << std::endl;
        return 1;
    }
    
    if (!Files::accesible(Files::homedir() + "/.config/kdewe/config.json")) {
        std::cout << "Unable to access " + Files::homedir() + "/.config/kdewe/config.json" << std::endl;
        return 1;
    }

    JSON json = JSON::parse(Files::read(Files::homedir() + "/.config/kdewe/config.json"));

    JSONValue steamdir = json.get("STEAMDIR");

    if (steamdir.type != JSONType::JSON_STRING) {
        std::cout << "Unable to find STEAMDIR in config.json" << std::endl;
    }

    Plugin::change_wallpaper(JSONValue::String(steamdir), argv[1]);

    return 0;
}