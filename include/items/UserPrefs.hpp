#ifndef ACCOUNT_PREFS_HPP
#define ACCOUNT_PREFS_HPP

#include <vector>
#include <string>
#include "include/base/Types.hpp"


typedef struct _prefs {
	std::string accept_pms;
	bool allow_clicktracking;
	bool beta;
	bool clickgadget;
	bool compress;
	std::vector< std::string > content_langs;
	bool creddit_autorenew;
	//std::string default_comment_sort;
	SortType default_comment_sort;
	std::string default_theme_sr; // this can be nullified
	bool domain_details;
	bool email_digests;
	bool email_messages;
	bool enable_default_themes;
	std::string geopopular;
	//bool hide_abusive_comments; -- this variable for some reason stop existing :/
	bool hide_ads;
	bool hide_downs;
	bool hide_from_robots;
	bool hide_locationbar;
	bool hide_ups;
	bool highlight_controversial;
	bool highlight_new_comments;
	bool ignore_suggested_sort;
	bool label_nsfw;
	std::string lang;
	bool legacy_search;
	bool live_orangereds;
	bool mark_messages_read;
	std::string media;
	std::string media_preview;
	int min_comment_score;
	int min_link_score;
	bool monitor_mentions;
	bool newwindow;
	bool no_profanity;
	bool no_video_autoplay;
	int num_comments;
	int numsites;
	bool organic;
	bool over_18;
	bool private_feeds;
	bool public_votes;
	bool research;
	bool search_include_over_18;
	bool show_flair;
	bool show_link_flair;
	bool show_gold_expiration;
	std::string show_promote; // can be nullified
	bool show_snoovatar;
	bool show_stylesheets;
	bool show_trending;
	bool store_visits;
	bool threaded_messages;
	bool threaded_modmail;
	bool top_karma_subreddits;
	bool use_global_defaults;
	Region g;
	//std::string other_theme;
	//std::string theme_selector;
	
	
}UserPrefs;

#endif
