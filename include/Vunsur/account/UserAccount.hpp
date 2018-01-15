#ifndef UserAccount_HPP
#define UserAccount_HPP

#include "base/Created.hpp"
#include "base/BaseThing.hpp"
#include "Holdout.hpp"
#include "UserSubreddit.hpp"

#include <string>

// This structure that stores user information for any account
class UserAccount : public Created, public BaseThing {
	public:
		UserAccount();
		~UserAccount();
		
		int comment_karma;
		//long created;
		//long created_utc;
					
		// Features
		bool activity_service_read;
		bool activity_service_write;
		bool adblock_test;
		bool ads_auction;
		bool ads_auto_extend;
		bool ads_auto_refund;
		bool adserver_reporting;
		bool adzerk_do_not_track;
		bool adzerk_reporting_2;
		
		bool chat;
		Holdout* default_srs_holdout;
		
		bool do_not_track;
		bool eu_cookie_policy;
		bool expando_events;
		bool force_https;
		bool geopopular;
		Holdout* geopopular_gb_holdout;
		Holdout* geopopular_ie_holdout;
		Holdout* geopopular_in_holdout;
		Holdout* geopopular_tw_holdout;
		
		bool give_hsts_grants;
		bool https_redirect;
		bool inbox_push;
		bool interest_targeting;
		bool legacy_search_pref;
		bool listing_service_rampup;
		bool live_happening_now;
		bool live_orangereds;
		bool loadtest_sendbird_me;
		bool moat_tracking;
		bool mobile_native_banner;
		bool mobile_web_targeting;
		Holdout* mweb_xpromo_ad_feed_ios;
		bool mweb_xpromo_interstitial_comments_android;
		bool mweb_xpromo_interstitial_comments_ios;
		bool mweb_xpromo_modal_listing_click_daily_dismissible_android;
		bool mweb_xpromo_modal_listing_click_daily_dismissible_ios;
		bool new_loggedin_cache_policy;
		bool new_overview;
		bool new_report_dialog;
		bool new_report_flow;
		bool orangereds_as_emails;
		bool outbound_clicktracking;
		bool pause_ads;
		bool personalization_prefs;
		bool post_embed;
		bool post_to_profile_beta;
		bool programmatic_ads;
		bool screenview_events;
		bool scroll_events;
		bool search_dark_traffic;
		Holdout* search_public_traffic;
		bool show_amp_link;
		bool show_recommended_link;
		bool show_user_sr_name;
		bool subreddit_rules;
		bool upgrade_cookies;
		bool users_listing;
		bool whitelisted_pms;
		// End features
		
		int gold_creddits;
		long gold_expiration; // nullible
		bool has_mail;
		bool has_mod_mail;
		bool has_subscribed;
		bool has_verified_email;
		bool hide_from_robots;
		std::string id;
		bool in_beta;
		int inbox_count;
		bool is_employee;
		bool is_gold;
		bool is_mod;
		bool is_sponsor;
		bool is_suspended;
		int link_karma;
		bool new_modmail_exists;
		std::string oauth_client_id;
		bool over_18;
		std::string pref_geopopular;
		bool pref_no_profanity;
		bool pref_show_snoovatar;
		bool pref_top_karma_subreddits;
		
		UserSubreddit* subreddit;
		
		long suspension_expiration_utc; // nullifiable
		bool verified;
		
				
};

#endif
