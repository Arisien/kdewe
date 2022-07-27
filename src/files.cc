/**
 * @file files.cc
 * @author arisien (arisien@vivaldi.net)
 * @brief Function implementations for File management.
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <string>

namespace Files {

    std::string homedir () {
        char* chrptr = getenv("HOME");

        if (chrptr == NULL) {
            throw std::runtime_error("Files::homedir > Unable to get HOME directory");
        }

        std::string str = chrptr;

        return str;
    }

    bool accesible (std::string path) {
        FILE* file = fopen(path.c_str(), "r");

        if (file) {
            fclose(file);
            return true;
        }

        return false;
    }

    std::string read (std::string path) {
        FILE* file = fopen(path.c_str(), "r");

        if (!file) {
            throw std::runtime_error("Files::read > Unable to open " + path);
        }

        size_t len;

        fseek(file, 0, SEEK_END);
        len = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* buf = (char*) malloc(len);

        fread(buf, 1, len, file);

        std::string str = buf;

        free(buf);

        fclose(file);

        return str;
    }

    void write (std::string path, std::string src) {
        FILE* file = fopen(path.c_str(), "w");

        if (!file) {
            throw std::runtime_error("Files::write > Unable to open " + path);
        }

        fwrite(src.c_str(), 1, src.length(),  file);

        fclose(file);
    }
}