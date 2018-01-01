#ifndef AUTHDATA_HPP
#define AUTHDATA_HPP

#include <string>
#include <ctime>

typedef struct authdat
{
	std::string token;
	std::string token_type;
	std::string scope;
	struct tm * expire;
	std::string userAgent;
	char* modhash;
}AccessData;

#endif
