/**
 * @file jsonvalue.cc
 * @author arisien (arisien@vivaldi.net)
 * @brief Function implementations for values in JSON objects.
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "jsonvalue.hh"

JSONValue::JSONValue () {
    this->type = JSON_UNDEFINED;
}

JSONValue::JSONValue (bool b) {
    this->type = JSON_BOOL;
    this->b = b;
}

JSONValue::JSONValue (double d) {
    this->type = JSON_NUMBER;
    this->d = d;
}

JSONValue::JSONValue (std::string s) {
    this->type = JSON_STRING;
    this->s = s;
}

JSONValue::JSONValue (std::vector<JSONValue> v) {
    this->type = JSON_ARRAY;
    this->v = v;
}

JSONValue::JSONValue (JSON j) {
    this->type = JSON_OBJECT;
    this->j = j;
}

bool JSONValue::Bool (JSONValue value) {
    return value.b;
}
        
double JSONValue::Number (JSONValue value) {
    return value.d;
}

std::string JSONValue::String (JSONValue value) {
    return value.s;
}

std::vector<JSONValue> JSONValue::Array (JSONValue value) {
    return value.v;
}

JSON JSONValue::Object (JSONValue value) {
    return value.j;
}

JSONValue JSONValue::parse (std::string src) {
    JSONValue value;

    size_t cursor = 0;

    while (src[cursor] == ' ' || src[cursor] == '\t' || src[cursor] == '\n') cursor++;

    // JSON_NUMBER
    if (src[cursor] >= '0' && src[cursor] <= '9') {
        std::string str = "";

        while (cursor < src.length() && (src[cursor] == '.' || (src[cursor] >= '0' && src[cursor] <= '9'))) {
            str += src[cursor];
            cursor++;
        }

        value = JSONValue(std::stod(str));
        value.len = cursor;

        return value;
    }

    switch (src[cursor]) {
        // JSON_BOOL
        case 't': {
            std::string str = src.substr(cursor, 4);
            if (str == "true") {
                value = JSONValue(true);
                cursor += 4;
            }
            else {
                throw std::runtime_error("JSONValue::parse > Expected true but got " + src.substr(cursor, 4));
            }
            break;
        }
        case 'f': {
            std::string str = src.substr(cursor, 5);
            if (str == "false") {
                value = JSONValue(false);
                cursor += 5;
            }
            else {
                throw std::runtime_error("JSONValue::parse > Expected false but got " + src.substr(cursor, 5));
            }
            break;
        }
        case '\"': {
            cursor++;
            std::string str = "";
            while (cursor < src.length() && src[cursor] != '"') {
                str += src[cursor];
                cursor++;
            }
            if (cursor < src.length()) {
                value = JSONValue(str);
            }
            else {
                throw std::runtime_error("JSONValue::parse > Unexpectededly reached end of file when parsing string: " + str);
            }
            cursor++;
            break;
        }
        case '[': {
            cursor++;
            
            std::vector<JSONValue> values;

            while (cursor < src.length()) {
                value = JSONValue::parse(src.substr(cursor, src.length() - cursor));

                if (value.type != JSON_UNDEFINED) {
                    values.push_back(value);
                }

                cursor += value.len;

                if (src[cursor] == ']') {
                    cursor++;
                    break;
                }

                if (src[cursor] != ',') {
                    throw std::runtime_error("JSON::parse > Unexpected token " + std::string({src[cursor]}) + " at " + std::to_string(cursor));
                }

                cursor++;
            }

            value = JSONValue(values);

            break;
        }
        case '{': {
            value = JSONValue(JSON::parse(src.substr(cursor, src.length() - cursor)));
            value.len = value.j.len;
            return value;
        }
        default:
            value = JSONValue();
            break;
    }

    value.len = cursor;
    return value;

}

std::string JSONValue::serialize (JSONValue value) {
    std::string serialized = "";
    switch (value.type) {
        case JSON_BOOL:
            if (JSONValue::Bool(value)) serialized += "true";
            else serialized += "false";
            break;
        case JSON_NUMBER:
            serialized += std::to_string(JSONValue::Number(value));
            break;
        case JSON_STRING:
            serialized += "\"" + JSONValue::String(value) + "\"";
            break;
        case JSON_ARRAY: {
            serialized += "[";
            std::vector<JSONValue> values = JSONValue::Array(value);
            for (size_t i = 0; i < values.size(); i++) {
                serialized += serialize(values[i]);
                if (i < values.size() - 1) serialized += ",";
            }
            serialized += "]";
            break;
        }
        case JSON_OBJECT:
            serialized += JSON::serialize(JSONValue::Object(value));
            break;
        default:
            break;
    }
    return serialized;
}