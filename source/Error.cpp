#include "include/Error.hpp"
#include <iostream>

void set_curl_handle_error( Status& s )
{
	#ifdef DEBUG
	std::cout << "Error: Failed to initialize CURL *handle " << std::endl;
	#endif
	
	s.code = NULL;
	s.cstat = ERROR_CURL_HANDLE_FAILED_INIT;
	s.message = "Error: Failed to initialize CURL *handle ";
}


void set_curl_global_error( Status& s )
{
	#ifdef DEBUG
	std::cout << "Error: Failed to initialize CURL GLOBAL " << std::endl;
	#endif
	
	s.code = NULL;
	s.cstat = ERROR_CURL_GLOBAL_FAILED_INIT;
	s.message = "Error: Failed to initialize CURL GLOBAL ";
}

void set_curl_strerror( Status& s, CURLcode result )
{
	#ifdef DEBUG
	std::cout << curl_easy_strerror(result) << std::endl;
	#endif
	
	s.cstat = ERROR_CURL_STRERROR;
	s.message = curl_easy_strerror(result);
}

void api_error(Status& s, int code, std::string message)
{
	s.cstat = ERROR_NONE;
	s.code = code;
	s.message = message;
}

void array_error( Status& s )
{
	#ifdef DEBUG
	std::cout << "Error: Failed to parse json children " << std::endl;
	#endif
	
	s.cstat = ERROR_JSONERROR;
	s.message = "Error: Failed to parse json children ";
}

void not_an_array_error( Status& s, std::string array_name )
{
	#ifdef DEBUG
	std::cout << "Error: " << array_name << " is not an array " << std::endl;
	#endif
	
	std::string es = "Error: ";
	es += array_name;
	es += " is not an array ";
	
	s.cstat = ERROR_JSONERROR;
	s.message = es;
}

void unknown_error( Status& s )
{
	#ifdef DEBUG
	std::cout << "Error: Unknown error " << std::endl;
	#endif
	
	s.cstat = ERROR_UNKNOWN_ERROR;
	s.message = "Error: Unknown error";
}

void bad_alloc_error( Status& s )
{
	#ifdef DEBUG
	std::cout << "Error: Bad allocation! " << std::endl;
	#endif
	
	s.cstat = ERROR_BAD_ALLOCATION;
	s.message = "Error: Bad allocation! ";
}

void not_logged_in( Status& s ) {
	s.code = NULL;
	s.cstat = ERROR_NOT_LOGGED_IN;
	s.message = "Error: Not logged in";
}
