#ifndef PERMALINK_COMMENT_HPP
#define PERMALINK_COMMENT_HPP

#include "subreddit/comments/Comment.hpp"

typedef struct pcomm : public Comment {
	bool brand_safe;
	bool clicked;
	bool clicked;
	std::string domain;
	bool hidden;
	bool is_crosspostable;
	bool is_reddit_media_domain;
	bool is_self;
	bool is_video;
	bool locked;
	//T media -- need more information
	//std::vector< T > media_embed;
	int num_comments;
	int num_crossposts;
	bool over_18;
	//std::string parent_whitelist_status; -- need more information
	std::string permalink;
	bool pinned;
	bool quarantine;
	//T secure_media -- not enough info
	//std::vector< T > secure_media_embed -- not enough info
	std::string selftext;
	std::string selftext_html;
	bool spoiler;
	std::string suggested_sort; // nullable
	std::string thumbnail;
	int thumbnail_height;
	int thumbnail_width;
	std::string title;
	float upvote_ratio;
	std::string url;
	int view_count;
	bool visited;
	std::string whitelist_status; // nullable
}PermaComment;
#endif
