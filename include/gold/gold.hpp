#ifndef REDDITGOLD_HPP
#define REDDITGOLD_HPP

#include <curl/curl.h>
#include <string>
#include "include/authdata.hpp"
#include "include/condition.hpp"
#include "include/Error.hpp"

// Gilds a thing
Status gild( AccessData* dat, std::string fullname ); // not tested
// Gives gold to a person
Status give_gold( AccessData* dat, std::string username ); // not tested
#endif
