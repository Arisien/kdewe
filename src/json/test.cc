/**
 * @file test.cc
 * @author arisien (arisien@vivaldi.net)
 * @brief Testing file for KDEWE json library.
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>

#include "jsonvalue.cc"
#include "json.cc"

int main (void) {
    JSON json;

    json.put("isWorking", JSONValue(true));
    json.put("pi", JSONValue(3.14));
    json.put("str", JSONValue(std::string("Hello, World!")));
    json.put("arr", JSONValue(std::vector<JSONValue>({JSONValue(1.0), JSONValue(2.0), JSONValue(3.0)})));

    std::string serialized = JSON::serialize(json);

    std::cout << serialized << std::endl;

    JSON j = JSON::parse(serialized);

    std::cout << JSON::serialize(j) << std::endl;

    return 0;
}