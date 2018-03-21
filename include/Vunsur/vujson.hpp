#ifndef VUJSON_HPP
#define VUJSON_HPP

#include "json.hpp"
#include <typeinfo>
#include <string>

bool get_boolean_value(nlohmann::json src);
long get_long_value(nlohmann::json src);
int get_integer_value(nlohmann::json src);
std::string get_string_value(nlohmann::json src);

#endif

