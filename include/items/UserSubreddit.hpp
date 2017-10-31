#ifndef USERSUB_HPP
#define USERSUB_HPP

#include <vector>


typedef struct _usrsub {
	std::string audience_target; // nullifiable
	std::string banner_img; // nullifiable
	std::vector<int> banner_size; // max 2
	
	std::string description;
	std::string display_name;
	std::string display_name_prefixed;
	
	std::string header_img; // nullifiable
	std::vector<int> header_size; // nullifiable, max 2
	
	std::string icon_img; // nullifiable
	std::vector<int> icon_size; // nullifiable, max 2
	
	bool is_default_banner;
	bool is_default_icon;
	std::string key_color;
	bool link_flair_enabled;
	std::string name;
	bool over_18;
	std::string public_description;
	bool show_media;
	std::string subreddit_type;
	int subscribers;
	std::string title;
	std::string url;
	bool user_is_banned;
	bool user_is_contributor;
	bool user_is_moderator;
	bool user_is_muted;
	bool user_is_subscriber;
}UserSubreddit;
#endif
