#include "vujson.hpp"


template< class T > 
T get_value( nlohmann::json p )
{	
	if( !p.is_null() && (p.is_number() || p.is_string() || p.is_boolean()))
	{
		return p.get<T>();
	} else {
		switch( sizeof(T) ) {
			case sizeof(std::string): return "";
			case sizeof(int): return 0;
			default: return 0;
		}
	}
}
