#ifndef AUTHDATA_HPP
#define AUTHDATA_HPP

#include <string>
#include <ctime>

class AccessData
{
	public:

		std::string token;
		std::string token_type;
		std::string scope;
		struct tm * expire;
		std::string userAgent;
};

#endif
