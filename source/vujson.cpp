#include "vujson.hpp"


bool get_boolean_value(nlohmann::json src)
{
	if (!src.is_null() && src.is_boolean())
		return src.get<bool>();
	else
		return false;
}

long get_long_value(nlohmann::json src)
{
	if (!src.is_null() && src.is_number_integer())
		return src.get<long>();
	else
		return NULL;
}

int get_integer_value(nlohmann::json src)
{
	if (!src.is_null() && src.is_number())
		return src.get<int>();
	else
		return NULL;
}

std::string get_string_value(nlohmann::json src)
{
	if (!src.is_null() && src.is_string())
		return src.get<std::string>();
	else
		return std::string();
}