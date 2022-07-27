/**
 * @file jsonvalue.hh
 * @author arisien (arisien@vivaldi.net)
 * @brief Definitions for values in JSON objects.
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef KDEWE_JSON_VALUE_HH
#define KDEWE_JSON_VALUE_HH

#include <stdexcept>
#include <cstring>
#include <string>
#include <vector>

#include "json.hh"

enum JSONType {
    JSON_BOOL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT,
    JSON_UNDEFINED
};

class JSONValue {
    public:
        unsigned char type;

        bool b;

        double d;

        std::string s;

        std::vector<JSONValue> v;

        JSON j;

        size_t len;

        JSONValue ();

        JSONValue (bool b);

        JSONValue (std::string s);
        
        JSONValue (double d);

        JSONValue (std::vector<JSONValue> v);

        JSONValue (JSON j);

        static bool Bool (JSONValue value);
        
        static double Number (JSONValue value);

        static std::string String (JSONValue value);

        static std::vector<JSONValue> Array (JSONValue value);

        static JSON Object (JSONValue value);

        static JSONValue parse (std::string src);

        static std::string serialize (JSONValue value);
        
};

class JSONPair {
    public:
        std::string key;
        JSONValue value;
};

#endif