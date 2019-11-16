#pragma once

#include "curl/curl.h"
#include "nlohmann/json.hpp"
#include <string>

namespace Vunsur{
template<class T>
  T get_numeric_value(nlohmann::json src);
  bool get_boolean_value(nlohmann::json src);
  std::string get_string_value(nlohmann::json src);
}
