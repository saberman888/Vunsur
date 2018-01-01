#ifndef REDDITGOLD_HPP
#define REDDITGOLD_HPP

#include <curl/curl.h>
#include <string>

#include "authdata.hpp"
#include "condition.hpp"
#include "Error.hpp"

// Gilds a thing
Status gild( AccessData* dat, std::string fullname ); // not tested
// Gives gold to a person
Status give_gold( AccessData* dat, std::string username ); // not tested
#endif
