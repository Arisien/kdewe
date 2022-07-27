/**
 * @file json.cc
 * @author arisien (arisien@vivaldi.net)
 * @brief Function implementations for JSON objects.
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "json.hh"

JSON::JSON () {}

void JSON::put (std::string str, JSONValue value) {
    content.insert(std::pair<std::string, JSONValue>(str, value));
}

JSONValue JSON::get (std::string str) {
    auto it = content.find(str);
    return it->second;
}


JSON JSON::parse (std::string src) {
    JSON json;

    if (src[0] != '{') {
        std::cout << "Parsing Exception at start" << std::endl;
        return json;
    }

    size_t cursor = 1;

    while (cursor < src.length()) {
        while (src[cursor] == ' ' || src[cursor] == '\t' || src[cursor] == '\n') cursor++;

        if (src[cursor] != '"') {
            std::cout << "[JSON] Parsing Exception at " << cursor << ": Expecting \" but got " << src[cursor] << std::endl;
            return json;
        }

        cursor++;

        std::string key = "";

        while (cursor < src.length() && src[cursor] != '"') {
            key += src[cursor];
            cursor++;
        }

        if (src[cursor] != '"') {
            std::cout << "[JSON] Parsing Exception at " << cursor << ": Expecting \" but reached file end." << std::endl;
            return json;
        }

        cursor += 2;

        JSONValue value = JSONValue::parse(src.substr(cursor, src.length() - cursor));

        json.put(key, value);
        
        cursor += value.len;

        if (src[cursor] == '}') break;

        if (src[cursor] != ',') {
            std::cout << "[JSON] Parsing Exception at " << cursor << ": Expecting , but got " << src[cursor] << std::endl;
            return json;
        }

        cursor++;
    }

    json.len = cursor;

    return json;
}

std::string JSON::serialize (JSON json) {
    std::string serialized = "{";
    for (auto itr = json.content.begin(); itr != json.content.end(); ++itr) {
        serialized += "\"" + itr->first + "\":";

        serialized += JSONValue::serialize(itr->second);

        serialized += ",";
    }
    serialized.pop_back();

    serialized += "}";

    return serialized;
}

