#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>


struct NoMainKeys : public std::exception 
{
	const char* what() const throw() {
		return "NoMainKeysError: There needs to be a client_id and a secret";
	}
};

struct NoUserAgent : public std::exception {
	const char* what() const throw() {
		return "NoUserAgentError: Error, no user agent found";
	}
};



struct FailedToExtractFromJsonData : public std::exception {
	const char * what() const throw() {
		return "FailedToExtractFromJsonDataError: Error, failed to extract data from json data";
	}
};

#endif
