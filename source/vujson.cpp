#include "vunsur/vujson.hpp"

namespace Vunsur {
  
  template<class T>
  T get_numeric_value(nlohmann::json src)
  {
    try {
      if(!src.is_null() && src.is_number())
        return src.get<T>();
    }catch(nlohmann::json&) {}
    return NULL;
  }

  bool get_boolean_value(nlohmann::json src)
  {
    try {
      if(!src.is_null() && src.is_boolean())
        return src.get<bool>();
    }catch(nlohmann::json&) {}
    return false;
  }

  std::string get_string_value(nlohmann::json src);
  {
    try {
      if(!src.is_null() && src.is_string())
        return src.get<std::string>();
    }catch(nlohmann::json&) {}
    return "";
  }
}
