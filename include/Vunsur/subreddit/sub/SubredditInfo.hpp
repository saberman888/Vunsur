#ifndef SUBREDDITINFO_HPP
#define SUBREDDITINFO_HPP

#include <vector>
#include "base/BaseThing.hpp"
#include "base/Created.hpp"

typedef struct subinfo : public BaseThing, public Created {
	int accounts_active;
	bool accounts_active_is_fuzzed;
	int active_user_count;
	std::string advertiser_category; // nullifiable
	bool allow_discovery;
	bool allow_images;
	bool allow_videos;
	bool allow_videogifs;
	std::string audience_target;
	std::string banner_img;
	std::vector<int> banner_size;
	bool collapse_deleted_comments;
	int comment_score_hide_mins;
	std::string description;
	std::string description_html;
	std::string display_name;
	std::string display_name_prefixed;
	std::string header_img;
	std::vector<int> header_size;
	std::string header_title;
	bool hide_ads;
	std::string icon_img;
	std::vector<int> icon_size;
	bool is_enrolled_in_new_modmail; // nullifiable
	std::string key_color;
	std::string lang;
	bool link_flair_enabled;
	bool over18;
	std::string public_description;
	std::string public_description_html;
	bool public_traffic;
	bool quarantine;
	bool show_media;
	bool show_media_preview;
	bool spoilers_enabled;
	std::string submission_type;
	std::string submit_link_label;
	std::string submit_text;
	std::string submit_text_html; // Nullifiable
	std::string submit_text_label;
	std::string subreddit_type;
	int subscribers;
	SortType suggested_comment_sort; // Nullifiable
	std::string title;
	std::string url;
	bool user_can_flair_in_sr;
	std::string user_flair_css_class;
	bool user_flair_enabled_in_sr;
	std::string user_flair_text;
	bool user_has_favorited;
	bool user_is_banned;
	bool user_is_contributor;
	bool user_is_moderator;
	bool user_is_muted;
	bool user_is_subscriber;
	bool user_sr_flair_enabled;
	bool user_sr_theme_enabled;
	std::string whitelist_status;
	bool wiki_enabled;
	

}SubredditInfo;

#endif
