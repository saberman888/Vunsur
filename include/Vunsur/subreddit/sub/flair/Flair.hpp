#ifndef FLAIR_FUNCTIONS_HPP
#define FLAIR_FUNCTIONS_HPP

#include "curl/curl.h"
#include "nlohmann/json.hpp"
#include <string>
#include <iosfwd>

#include "authdata.hpp"
#include "condition.hpp"
#include "Error.hpp"
#include "Info.hpp"


typedef enum tflair {
	USER_FLAIR = 0,
	LINK_FLAIR
}FlairType;

Status clear_flair_templates( AccessData* dat, std::string subreddit, FlairType ft );
Status delete_flair( AccessData* dat, std::string subreddit, std::string flair_template_name );

#endif
