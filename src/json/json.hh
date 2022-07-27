/**
 * @file json.hh
 * @author arisien (arisien@vivaldi.net)
 * @brief Definitions for JSON objects.
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef KDEWE_JSON_HH
#define KDEWE_JSON_HH

#include <string>
#include <map>

#include "jsonvalue.hh"

// WHY???
class JSONValue;


class JSON {
    public:
        std::map<std::string, JSONValue> content;

        size_t len;

        JSON();

        void put (std::string str, JSONValue value);

        JSONValue get (std::string str);

        static JSON parse (std::string src);

        static std::string serialize (JSON json);
};


#endif