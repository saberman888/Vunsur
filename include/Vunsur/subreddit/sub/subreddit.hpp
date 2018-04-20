#ifndef SUBREDDIT_HPP
#define SUBREDDIT_HPP

#include "nlohmann/json.hpp"
#include "curl/curl.h"
#include <iosfwd>
#include <string>

#include "Info.hpp"
#include "condition.hpp"
#include "authdata.hpp"
#include "Error.hpp"

#include "base/Types.hpp"

#include "subreddit/sub/SubredditInfo.hpp"

Status subreddit_about( AccessData* acd, std::string subreddit, SubredditInfo* subi );
Status subreddit_about_edit( AccessData* acd, std::string subreddit );
#endif
