#ifndef SUBREDDIT_HPP
#define SUBREDDIT_HPP

#include "curl/curl.h"
#include <iosfwd>
#include <string>

#include "include/Info.hpp"
#include "include/condition.hpp"
#include "include/authdata.hpp"
#include "include/Error.hpp"

Status subreddit_about( AccessData* acd, std::string subreddit );





#endif
