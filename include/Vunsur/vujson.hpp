#ifndef VUJSON_HPP
#define VUJSON_HPP

#include "json.hpp"

#include <typeinfo>

template< class T > 
T get_value( nlohmann::json p );

#endif

