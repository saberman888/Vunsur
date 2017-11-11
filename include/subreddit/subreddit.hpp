#ifndef SUBREDDIT_HPP
#define SUBREDDIT_HPP

#include "curl/curl.h"
#include <iosfwd>
#include <string>

#include "include/Info.hpp"
#include "include/condition.hpp"
#include "include/authdata.hpp"
#include "include/Error.hpp"
#include "include/base/Types.hpp"
#include "include/items/SubredditInfo.hpp"
#include "json.hpp"

Status subreddit_about( AccessData* acd, std::string subreddit, SubredditInfo* subi );





#endif
