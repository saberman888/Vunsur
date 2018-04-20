#ifndef VUNCOMMENT_HPP
#define VUNCOMMENT_HPP

#include "Comment.hpp"
#include "Error.hpp"
#include "vujson.hpp"
#include "condition.hpp"
#include "nlohmann/json.hpp"
#include <iosfwd>

class VunComment
{
public:
	VunComment(nlohmann::json src);
	VunComment();

	CommentSource source;
	std::vector< VunComment* > replies;
	size_t size();
	CommentSource& operator~();
	void get_replies(nlohmann::json& src);
	void get_more_replies();
	void read(nlohmann::json& src);
	/*
	Example:
	VunComment mycomm = [ POINTING TO A COMMENT ]

	Use ~ operator to access comment directly
	std::cout << ~mycomm.depth << std::endl;
	*/
};


#endif