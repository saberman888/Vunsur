#ifndef BasicUser_HPP
#define BasicUser_HPP

#include <string>

// A basics structure for data that only has few variables to represent a user
typedef struct _bsu
{
	long date;
	std::string id;
	std::string name;
}BasicUser;

#endif