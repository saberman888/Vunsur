#include "vujson.hpp"


template< class T > 
T get_value( nlohmann::json src )
{	
	std::type_info t_data = typeid(T);
	nlohmann::json p = nlohmann::json::parse(src);
	if(t_data == typeid(int) || t_data == typeid(long) || t_data == typeid(std::string))
	{
		if( !p.is_null() && (p.is_number() || p.is_string()) )
		{
			return p.dump();
		} else {
			if( typeid(std::string) ) return "";
			return 0;
		}
	} else if( t_data = typeid(bool) ) {
		if( !p.is_null() && p.is_boolean() ) {
			return p.dump();
		} else {
			return false;
		}
	}
}
