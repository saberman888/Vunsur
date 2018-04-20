#include "vujson.hpp"

bool does_value_exist(nlohmann::json tag, std::string name)
{
	bool exist = true;
	try {
		nlohmann::json Tag = tag.at(name);
	}
	catch (nlohmann::json::out_of_range) {
		exist = false;
	}
	return exist;
}

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

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
	((std::string*)stream)->append((char*)ptr, 0, size*count);
	return size * count;
}