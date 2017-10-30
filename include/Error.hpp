#ifndef ERROR_HPP
#define ERROR_HPP

#include "include/condition.hpp"
#include "curl/curl.h"
#include <string>

void set_curl_handle_error( Status& s );
void set_curl_global_error( Status& s );
void set_curl_strerror( Status& s, CURLcode result );

void api_error(Status& s, int code, std::string message);
void nlohmann_error(Status& s);

void array_error( Status& s );
void not_an_array_error( Status& s, std::string array_name );
void unknown_error( Status& s );
void bad_alloc_error( Status& s );
void not_logged_in(Status& s );
void no_modhash(Status& s );
void json_error(Status& s, std::string message);
#endif
