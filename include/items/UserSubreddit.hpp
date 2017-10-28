#ifndef USERSUB_HPP
#define USERSUB_HPP


typedef struct _usrsub {
	std::string audience_target; // nullifiable
	std::string banner_img; // nullifiable
	int banner_size[2];
	
	std::string description;
	std::string display_name;
	std::string display_name_prefixed;
	
	std::string header_img; // nullifiable
	int header_size[2]; // nullifiable
	
	std::string icon_img; // nullifiable
	int icon_size[2]; // nullifiable
	
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
