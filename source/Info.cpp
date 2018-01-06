#include "Info.hpp"


size_t writedat(char* buffer, size_t size, size_t nmemb, std::string& src)
{
	for( int i = 0; i < size * nmemb; i++ )
	{
		src.push_back(buffer[i]);
	}
	return size * nmemb;
}
