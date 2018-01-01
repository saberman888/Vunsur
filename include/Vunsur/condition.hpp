#ifndef VUN_RETURNS_HPP
#define VUN_RETURNS_HPP

#include <string>


// EStatus or _error_status is an enum that defines
// errors needed for the library
typedef enum _error_status
{
	ERROR_NONE,
	ERROR_CURL_HANDLE_FAILED_INIT,
	ERROR_CURL_GLOBAL_FAILED_INIT,
	ERROR_CURL_STRERROR,
	ERROR_NOT_LOGGED_IN,
	ERROR_UNSUPPORTED_GRANT_TYPE,
	ERROR_UNKNOWN_ERROR,
	ERROR_JSONERROR,
	ERROR_BAD_ALLOCATION,
	ERROR_NO_MODHASH
}EStatus;
// Status or _ret holds operation information like whether or not
// failure occured and it's specifics and etc
class Status
{
	public:
		std::string message;
		EStatus cstat;
		int code;
		
		Status();
		~Status();
		bool all_good();
};

// Prints out status
void print_status(Status s);
#endif
