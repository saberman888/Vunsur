#ifndef FLAIR_FUNCTIONS_HPP
#define FLAIR_FUNCTIONS_HPP

#include <curl/curl.h>
#include "json.hpp"
#include <string>
#include "include/authdata.hpp"
#include "include/condition.hpp"
#include "include/Error.hpp"
#include "include/Info.hpp"
#include <iosfwd>

typedef enum tflair {
	USER_FLAIR = 0,
	LINK_FLAIR
}FlairType;

Status clear_flair_templates( AccessData* dat, std::string subreddit, FlairType ft );

#endif
