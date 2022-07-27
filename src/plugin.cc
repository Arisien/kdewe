/**
 * @file plugin.cc
 * @author arisien (arisien@vivaldi.net)
 * @brief Function implementations for Plugin implementations.
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "plugin.hh"

namespace Plugin {

    void write_config (std::string entry, std::string value) {
        std::string cmd = "dbus-send --session --dest=org.kde.plasmashell --type=method_call /PlasmaShell org.kde.PlasmaShell.evaluateScript 'string: for (d of desktops()) { d.wallpaperPlugin = \"com.github.casout.wallpaperEngineKde\"; d.currentConfigGroup = Array(\"Wallpaper\", \"com.github.casout.wallpaperEngineKde\", \"General\"); d.writeConfig(\""+entry+"\", \""+value+"\"); }'";

        const char* chrptr = cmd.c_str();

        system(chrptr);
    }

    void set_display_mode (int mode) {
        write_config("DisplayMode", std::to_string(mode));
    }

    void change_wallpaper (std::string steamdir, std::string id) {
        if (!Files::accesible(steamdir + "/steamapps/workshop/content/431960/" + id)) {
            throw std::runtime_error("Plugin::change_wallpaper > Unable to find wallpaper " + id);
        }
        write_config("WallpaperWorkShopId", id);
        write_config("WallpaperSource", "file://" + steamdir + "/steamapps/workshop/content/431960/"+ id +"/scene.json+scene");   
    }

}