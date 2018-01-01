#ifndef LINK_AND_COMMENTS_HPP
#define LINK_AND_COMMENTS_HPP

#include "curl/curl.h"
#include "json.hpp"
#include <iosfwd>

#include "subreddit/sub/Post.hpp"

#include "subreddit/comments/Comment.hpp"
#include "subreddit/comments/Listing.hpp"

#include "base/Types.hpp"

#include "Error.hpp"
#include "condition.hpp"
#include "Info.hpp"
#include "authdata.hpp"


/* LISTINGS*/
Status get_trending( AccessData* acd ); // Does not work
Status get_id_by_name( AccessData* dat, std::vector< std::string> names );

/* LINKS AND COMMENTS */
Status comment( AccessData* dat, std::string parent, std::string text );
Status delete_comment( AccessData* dat, std::string fullname );
Status edit_user_comment( AccessData* dat, std::string text, std::string id );


#endif
