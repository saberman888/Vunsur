#ifndef BLEND_HPP
#define BLEND_HPP

#include "Post.hpp"
#include "Comment.hpp"

#include "base/Types.hpp"

/*
	The blend structure is suppose to hold either a Post type or a 
	Comment type. It is used in lists/Listings that have both posts and comments ( e.g saved )
*/
union BlendObject {
	Post* p;
	Comemnt* c;
};

struct Blend {
	VunType kind;
	union BlendObject object;
};

#endif
