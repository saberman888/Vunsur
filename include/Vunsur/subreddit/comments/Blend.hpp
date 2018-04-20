#ifndef BLEND_HPP
#define BLEND_HPP

#include "subreddit/sub/Post.hpp"
#include "subreddit/comments/VunComment.hpp"

#include "base/Types.hpp"

/*
	The blend structure is suppose to hold either a Post type or a 
	Comment type. It is used in lists/Listings that have both posts and comments ( e.g saved )
*/

typedef struct _BlendObject {
	VunComment c;
	Post p;
}BlendObject;

typedef struct _Blend {
		VunType kind;
		BlendObject object;
}Blend;

#endif
