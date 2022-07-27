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

    size_t cursor = 0;

    while (src[cursor] == ' ' || src[cursor] == '\t' || src[cursor] == '\n') cursor++;

    if (src[cursor] != '{') {
        throw std::runtime_error("JSON::parse > Unexpected token " + std::string({src[cursor]}) + " at " + std::to_string(cursor));
    }

    cursor++;

    while (cursor < src.length()) {
        while (src[cursor] == ' ' || src[cursor] == '\t' || src[cursor] == '\n') cursor++;

        if (src[cursor] != '"') {
            throw std::runtime_error("JSON::parse > Unexpected token " + std::string({src[cursor]}) + " at " + std::to_string(cursor));
        }

        cursor++;

        std::string key = "";

        while (cursor < src.length() && src[cursor] != '"') {
            key += src[cursor];
            cursor++;
        }

        if (src[cursor] != '"') {
            throw std::runtime_error("JSON::parse > Unexpectededly reached end of file when parsing string: " + key);
        }

        cursor++;

        while (src[cursor] == ' ' || src[cursor] == '\t' || src[cursor] == '\n') cursor++;

        if (src[cursor] != ':') {
            throw std::runtime_error("JSON::parse > Unexpected token " + std::string({src[cursor]}) + " at " + std::to_string(cursor));
        }
        cursor++;

        JSONValue value = JSONValue::parse(src.substr(cursor, src.length() - cursor));

        json.put(key, value);
        
        cursor += value.len;

        while (src[cursor] == ' ' || src[cursor] == '\t' || src[cursor] == '\n') cursor++;

        if (src[cursor] == '}') break;

        if (src[cursor] != ',') {
            throw std::runtime_error("JSON::parse > Unexpected token " + std::string({src[cursor]}) + " at " + std::to_string(cursor));
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

