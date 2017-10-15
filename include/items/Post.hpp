#ifndef POST_HPP
#define POST_HPP

#include "include/base/BaseThing.hpp"
#include "include/base/Votable.hpp"
#include "include/base/Created.hpp"
#include <string>

typedef struct r_post : public BaseThing, public Created, public Votable {
	std::string approved_by;
	int approved_by_utc;
	bool archived;
	
	std::string author;
	std::string author_flair_css_class;
	std::string author_flair_text;
	
	int banned_at_utc;
	std::string banned_by;
	
	bool brand_safe;
	bool can_guild;
	bool can_mod_post;
	bool clicked;
	bool contest_mode;
	
	std::string distinguished;
	std::string domain;
	
	bool edited;
	int gilded;
	bool hidden;
	bool hide_score;
	
	bool is_crosspostable;
	bool is_self;
	bool is_video;
	//bool likes;
	bool locked;
	

	std::string link_flair_css_class;
	std::string link_flair_text;
	// There is not enough information to implement these
	// variables below that are commented
	//std::vector<std::string> media_embed;
	//std::vector<std::string> mod_reports;
	//std::string media;
	
	int num_comments;
	int num_crossposts;
	int num_reports;
	
	bool over_18;
	std::string parent_whitelist_status;
	std::string permalink;
	std::string post_hint;
	// I also need to add preview for images and whatnot
	
	bool quarantine;
	//std::string removal_reason -- not enough information
	//std::string report_reasons -- not enough information
	bool saved;
	int score;
	std::string selftext;
	std::string selftext_html;
	bool spoiler;
	bool stickied;
	std::string subreddit;
	std::string subreddit_id;
	std::string subreddit_name_prefixed;
	std::string subreddit_type;
	//std::string suggested_sort; -- not enough information
	std::string thumbnail;
	int thumbnail_height;
	int thumbnail_width;
	std::string title;
	float upvote_ratio;
	std::string url;
	//std::vector<std::string> user_reports; -- not enough information
	int view_count;
	bool visited;
	std::string whitelist_status;
	
	
}Post;

#endif
