#pragma once

#include "nlohmann/json.hpp"
#include <typeinfo>
#include <string>

bool get_boolean_value(nlohmann::json src);
long get_long_value(nlohmann::json src);
int get_integer_value(nlohmann::json src);
bool does_value_exist(nlohmann::json tag, std::string name);
std::string get_string_value(nlohmann::json src);
size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);