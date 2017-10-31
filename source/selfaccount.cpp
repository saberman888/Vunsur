#include "include/account/selfaccount.hpp"
#include <iostream>


Status get_self(AccessData* dat, UserAccount* person)
{
	CURL *handle;
	CURLcode result;
	Status st;
	int status_code;
	handle = curl_easy_init();
	
	std::string returndata;
	
	if(handle)
	{
		CURLcode globalres = curl_global_init( CURL_GLOBAL_SSL );
		if(globalres == CURLE_OK)
		{
			struct curl_slist *header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			//curl_get_sets(handle, "https://oauth.reddit.com/api/v1/me", header, dat->userAgent, returndata);
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L  );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &returndata );
			
			result = curl_easy_perform( handle );
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &status_code);
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(st, result);
				
				return st;
			} else {
				
				#ifdef DEBUG
				std::cout << returndata << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("getme_json.json");
				out << returndata;
				#endif
				
				auto js = nlohmann::json::parse(returndata);

				UserAccount* usr = new UserAccount;
				if(!usr) {
					bad_alloc_error(st);
					//delete usr;
					return st;
				}
				
				try {
					usr->comment_karma = js.at("comment_karma");
					usr->created = js.at("created");
					usr->created_utc = js.at("created_utc");
					
					// begin features
					nlohmann::json j;
					try {
						j = js.at("features");
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						
						json_error(st, "Error: features does not exist"); return st;
					}
					
					/*usr->activity_service_read = j.at("activity_service_read");
					usr->activity_service_write = j.at("activity_service_write");
					usr->adblock_test = j.at("adblock_test");
					usr->ads_auction = j.at("ads_auction");
					usr->ads_auto_extend = j.at("ads_auto_extend");
					usr->ads_auto_refund = j.at("ads_auto_refund");
					usr->adserver_reporting = j.at("adserver_reporting");
					usr->adzerk_do_not_track = j.at("adzerk_do_not_track");
					usr->adzerk_reporting_2 = j.at("adzerk_reporting_2");
					
					usr->chat = j.at("chat");
					
					usr->default_srs_holdout = new Holdout;
					if(!usr->default_srs_holdout) {
						bad_alloc_error(st); return st;
					}*/
					
					nlohmann::json dsh;
					usr->default_srs_holdout = new Holdout;
					if( !usr->default_srs_holdout ) {
						bad_alloc_error(st);
						return st;
					}
					try {
						dsh = j.at("default_srs_holdout");
						
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						delete usr->default_srs_holdout;
						json_error(st, "Error: default_srs_holdout does not exist");
						return st;
					}
					
					usr->default_srs_holdout->experiment_id = dsh.at("experiment_id");
					usr->default_srs_holdout->owner = dsh.at("owner");
					usr->default_srs_holdout->variant = dsh.at("variant");
					
					usr->do_not_track = j.at("do_not_track");
					usr->eu_cookie_policy = j.at("eu_cookie_policy");
					usr->expando_events = j.at("expando_events");
					usr->force_https = j.at("force_https");
					usr->geopopular = j.at("geopopular");
					
					usr->geopopular_gb_holdout = new Holdout;
					if(!usr->geopopular_gb_holdout) {
						bad_alloc_error(st); return st;
					}
					
					try {
						dsh = j.at("geopopular_gb_holdout");
						
					} catch ( nlohmann::json::out_of_range& e ) {
						
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						delete usr->geopopular_gb_holdout;
						json_error(st, "Error: geopopular_gb_holdout does not exist"); return st;
					}
					
					usr->geopopular_gb_holdout->experiment_id = dsh.at("experiment_id");
					usr->geopopular_gb_holdout->owner = dsh.at("owner");
					usr->geopopular_gb_holdout->variant = dsh.at("variant");
					
					usr->geopopular_ie_holdout = new Holdout;
					if( !usr->geopopular_ie_holdout ) {
						bad_alloc_error(st); return st;
					}
					try {
						dsh = j.at("geopopular_ie_holdout");
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						delete usr->geopopular_ie_holdout;
						json_error(st, "Error: geopopular_ie_holdout does not exist"); return st;
					}
					
					usr->geopopular_ie_holdout->experiment_id = dsh.at("experiment_id");
					usr->geopopular_ie_holdout->owner = dsh.at("owner");
					usr->geopopular_ie_holdout->variant = dsh.at("variant");
					
					usr->geopopular_in_holdout = new Holdout;
					if( !usr->geopopular_in_holdout ) {
						bad_alloc_error(st); return st;
					}
					try {
						dsh = j.at("geopopular_in_holdout");
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						delete usr->geopopular_in_holdout;
						json_error(st, "Error: geopopular_in_holdout does not exist"); return st;
					}
					
					usr->geopopular_in_holdout->experiment_id = dsh.at("experiment_id");
					usr->geopopular_in_holdout->owner = dsh.at("owner");
					usr->geopopular_in_holdout->variant = dsh.at("variant");
					
					nlohmann::json geopop_tw;
					usr->geopopular_tw_holdout = new Holdout;
					if( !usr->geopopular_tw_holdout ) {
						bad_alloc_error(st);
						return st;
					}
					try {
						geopop_tw = j.at("geopopular_tw_holdout");
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						delete usr->geopopular_tw_holdout;
						json_error(st, "Error: geopopular_tw_holdout does not exist"); return st;
					}
					
					usr->geopopular_tw_holdout->experiment_id = geopop_tw.at("experiment_id");
					usr->geopopular_tw_holdout->owner = geopop_tw.at("owner");
					usr->geopopular_tw_holdout->variant = geopop_tw.at("variant");

					
					usr->give_hsts_grants = j.at("give_hsts_grants");
					usr->https_redirect = j.at("https_redirect");
					usr->inbox_count = js.at("inbox_count");
					usr->interest_targeting = j.at("interest_targeting");
					usr->legacy_search_pref = j.at("legacy_search_pref");
					usr->listing_service_rampup = j.at("listing_service_rampup");
					usr->live_happening_now = j.at("live_happening_now");
					usr->live_orangereds = j.at("live_orangereds");
					usr->loadtest_sendbird_me = j.at("loadtest_sendbird_me");
					usr->moat_tracking = j.at("moat_tracking");
					usr->mobile_native_banner = j.at("mobile_native_banner");
					usr->mobile_web_targeting = j.at("mobile_web_targeting");
					
					usr->mweb_xpromo_ad_feed_ios = new Holdout;
					if( usr->mweb_xpromo_ad_feed_ios ) {
						bad_alloc_error(st);
						return st;
					}
					try {
						dsh = j.at("mweb_xpromo_ad_feed_ios");
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						delete usr->mweb_xpromo_ad_feed_ios;
						json_error(st, "Error: mweb_xpromo_ad_feed_ios does not exist"); return st;
					}
					
					usr->mweb_xpromo_ad_feed_ios->experiment_id = dsh.at("experiment_id");
					usr->mweb_xpromo_ad_feed_ios->owner = dsh.at("owner");
					usr->mweb_xpromo_ad_feed_ios->variant = dsh.at("variant");
					
					usr->mweb_xpromo_interstitial_comments_android = j.at("mweb_xpromo_interstitial_comments_android");
					usr->mweb_xpromo_interstitial_comments_ios = j.at("mweb_xpromo_interstitial_comments_ios");
					
					usr->mweb_xpromo_modal_listing_click_daily_dismissible_android = j.at("mweb_xpromo_modal_listing_click_daily_dismissible_android");
					usr->mweb_xpromo_modal_listing_click_daily_dismissible_ios = j.at("mweb_xpromo_modal_listing_click_daily_dismissible_ios");
					
					usr->new_loggedin_cache_policy = j.at("new_loggedin_cache_policy");
					usr->new_overview = j.at("new_overview");
					usr->new_report_dialog = j.at("new_report_dialog");
					usr->new_report_flow = j.at("new_report_flow");
					usr->orangereds_as_emails = j.at("orangereds_as_emails");
					usr->outbound_clicktracking = j.at("outbound_clicktracking");
					usr->pause_ads = j.at("pause_ads");
					usr->personalization_prefs = j.at("personalization_prefs");
					usr->post_embed = j.at("post_embed");
					usr->post_to_profile_beta = j.at("post_to_profile_beta");
					usr->programmatic_ads = j.at("programmatic_ads");
					usr->screenview_events = j.at("screenview_events");
					usr->scroll_events = j.at("scroll_events");
					usr->search_dark_traffic = j.at("search_dark_traffic");
					
					usr->search_public_traffic = new Holdout;
					if( !usr->search_public_traffic ) {
						bad_alloc_error(st);
						return st;
					}
					try {
						dsh = j.at("search_public_traffic");
						
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						delete usr->search_public_traffic;
						json_error(st, "Error: search_public_traffic does not exist"); return st;
					}
					
					usr->search_public_traffic->experiment_id = dsh.at("experiment_id");
					usr->search_public_traffic->owner = dsh.at("owner");
					usr->search_public_traffic->variant = dsh.at("variant");
					
					usr->show_amp_link = j.at("show_amp_link");
					usr->show_recommended_link = j.at("show_recommended_link");
					usr->show_user_sr_name = j.at("show_user_sr_name");
					usr->subreddit_rules = j.at("subreddit_rules");
					usr->upgrade_cookies = j.at("upgrade_cookies");
					usr->users_listing = j.at("users_listing");
					usr->whitelisted_pms = j.at("whitelisted_pms");
					// end features
					
					usr->gold_creddits = js.at("gold_creddits");
					
					try {
						if( js.at("gold_expiration").is_null() ) {
							usr->gold_expiration = NULL;
						} else {
							usr->gold_expiration = js.at("gold_expiration");
						}
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						
						json_error(st, "Error: gold_expirations does not exist"); return st;
					}
					
					usr->has_mail = js.at("has_mail");
					usr->has_mod_mail = js.at("has_mod_mail");
					usr->has_subscribed = js.at("has_subscribed");
					usr->has_verified_email = js.at("has_verified_email");
					usr->hide_from_robots = js.at("hide_from_robots");
					usr->id = js.at("id");
					usr->in_beta = js.at("in_beta");
					usr->inbox_count = js.at("inbox_count");
					usr->is_employee = js.at("is_employee");
					usr->is_mod = js.at("is_mod");
					usr->is_sponsor = js.at("is_sponsor");
					usr->is_suspended = js.at("is_suspended");
					usr->link_karma = js.at("link_karma");
					usr->name = js.at("name");
					usr->new_modmail_exists = js.at("new_modmail_exists");
					usr->oauth_client_id = js.at("oauth_client_id");
					usr->over_18 = js.at("over_18");
					usr->pref_geopopular = js.at("pref_geopopular");
					usr->pref_no_profanity = js.at("pref_no_profanity");
					usr->pref_show_snoovatar = js.at("pref_show_snoovatar");
					usr->pref_top_karma_subreddits = js.at("pref_top_karma_subreddits");
					
					nlohmann::json sub;
					try {
						sub = js.at("subreddit");
					} catch( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						
						json_error(st, "Error: subreddit does not exist"); return st;
					}
					
					usr->subreddit = new UserSubreddit;
					if( !usr->subreddit ) {
						bad_alloc_error(st); return st;
					}
					
					usr->subreddit->audience_target = sub.at("audience_target");
					
					nlohmann::json bi = sub.at("banner_img");
					if( bi.is_null() ) {
						usr->subreddit->banner_img = "";
					} else {
						usr->subreddit->banner_img = sub.at("banner_img");
					}
					
					dsh = sub.at("banner_size");
					
					if( dsh.is_array() && !dsh.is_null() ) {
						usr->subreddit->banner_size.push_back(dsh[0]);
						usr->subreddit->banner_size.push_back(dsh[1]);
					} else {
						usr->subreddit->banner_size.push_back(0);
						usr->subreddit->banner_size.push_back(0);
					}
					usr->subreddit->description = sub.at("description");
					usr->subreddit->display_name = sub.at("display_name");
					usr->subreddit->display_name_prefixed = sub.at("display_name_prefixed");
					nlohmann::json h_i = sub.at("header_img");
					if( !h_i.is_null() ) {
						usr->subreddit->header_img = sub.at("header_img");
					} else {
						usr->subreddit->header_img = "";
					}
					
					h_i = sub.at("header_size");
					if( !h_i.is_array() && h_i.is_null() ) {
						usr->subreddit->header_size.push_back(0);
						usr->subreddit->header_size.push_back(0);
					} else {
						usr->subreddit->header_size.push_back(h_i[0]);
						usr->subreddit->header_size.push_back(h_i[1]);
					}
					
					dsh = sub.at("icon_img");
					if( !dsh.is_null() ) {
						usr->subreddit->icon_img = sub.at("icon_img");
					} else {
						usr->subreddit->icon_img = "";
					}
					
					h_i = sub.at("icon_size");
					if( !h_i.is_array() && h_i.is_null() ) {
						usr->subreddit->icon_size.push_back(0);
						usr->subreddit->icon_size.push_back(0);
					} else {
						usr->subreddit->icon_size.push_back(h_i[0]);
						usr->subreddit->icon_size.push_back(h_i[1]);
					}
					
					usr->subreddit->is_default_banner = sub.at("is_default_banner");
					usr->subreddit->is_default_icon = sub.at("is_default_icon");
					usr->subreddit->key_color = sub.at("key_color");
					usr->subreddit->link_flair_enabled = sub.at("link_flair_enabled");
					usr->subreddit->name = sub.at("name");
					usr->subreddit->over_18 = sub.at("over_18");
					usr->subreddit->public_description = sub.at("public_description");
					usr->subreddit->show_media = sub.at("show_media");
					usr->subreddit->subreddit_type = sub.at("subreddit_type");
					usr->subreddit->subscribers = sub.at("subscribers");
					usr->subreddit->title = sub.at("title");
					usr->subreddit->user_is_banned = sub.at("user_is_banned");
					usr->subreddit->user_is_contributor = sub.at("user_is_contributor");
					usr->subreddit->user_is_moderator = sub.at("user_is_moderator");
					usr->subreddit->user_is_muted = sub.at("user_is_muted");
					usr->subreddit->user_is_subscriber = sub.at("user_is_subscriber");
					
					
					nlohmann::json sus = js.at("suspension_expiration_utc");
					if( sus.is_null() ) {
						usr->suspension_expiration_utc = 0;
					} else {
						usr->suspension_expiration_utc = js.at("suspension_expiration_utc");
					}
					
					usr->verified = js.at("verified");
					
					
				} catch( nlohmann::json::out_of_range& e ) {
					try {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						
						std::string message = js.at("message");
						
						api_error(st, status_code, message);
						
						return st;
					} catch ( nlohmann::json::out_of_range& e ) {
						
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						
						unknown_error(st);
						return st;
					}
				}
				

				
				st.code = status_code;
				st.cstat = ERROR_NONE;
				st.message = "";
				
				return st;
			}
		} else {
			set_curl_global_error(st);
			return st;
		}
	} else {
		set_curl_handle_error(st);
		
		return st;
	}
	return st;
}

Status get_karma( AccessData* dat, std::vector<SubredditKarma*> *sbv )
{
	CURL *handle;
	CURLcode result;
	handle = curl_easy_init();
	std::string jsondata;
	int state;
	Status s;
	
	if( handle )
	{
		CURLcode globalResult = curl_global_init(CURL_GLOBAL_SSL);
		if( globalResult == CURLE_OK )
		{
			struct curl_slist* header = nullptr;
			std::string authheader = "Authorization: ";
			authheader += std::string(dat->token_type);
			authheader += " ";
			authheader += std::string(dat->token);
			
			header = curl_slist_append( header, authheader.c_str() );
			
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me/karma" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &jsondata );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform( handle );
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			if( result != CURLE_OK )
			{
				
				set_curl_strerror(s,result);
				
				return s;
			} else {
				
				#ifdef DEBUG
				std::cout << jsondata << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("get_karma_json.json");
				out << jsondata;
				#endif
				
				auto j = nlohmann::json::parse(jsondata);
				
				try {
					auto data_arr = j.at("data");
					if( data_arr.is_array() ) {
						
						for( auto& elem : data_arr )
						{
							int comment_karma = elem.at("comment_karma");
							int link_karma = elem.at("link_karma");
							std::string subreddit = elem.at("sr");
							
							//SubredditKarma* sbkarma = new SubredditKarma;
							struct sbkarma* sbkarma_ = new struct sbkarma;
							if(!sbkarma_)
							{
								bad_alloc_error(s);
								return s;
							}
							sbkarma_->comment_karma = comment_karma;
							sbkarma_->link_karma = link_karma;
							sbkarma_->subreddit = subreddit;
							
							sbv->push_back(sbkarma_);
						}
					} else {
						not_an_array_error(s, "data");
						return s;
					}
				} catch ( nlohmann::json::out_of_range& e ) { 
					try {
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						std::string message;
						int error;
							
						message = j.at("message");
						error = j.at("error");
							
						api_error(s, error, message);
							
						return s;
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						unknown_error(s);
						return s;
					}
				}
				
				s.cstat = ERROR_NONE;
				s.message = "";
				
				return s;
			}
		} else {
			
			set_curl_global_error(s);
			
			return s;
		}
	} else {
		
		set_curl_handle_error(s);
		
		return s;
	}
}

Status get_blocked_users(AccessData* dat)
{
	CURL *handle;
	CURLcode result;
	std::string jsondat;
	int state;
	Status s;
	handle = curl_easy_init();
	
	if(handle)
	{
		CURLcode globalRes = curl_global_init(CURL_GLOBAL_SSL);
		if(globalRes == CURLE_OK)
		{
		//	std::string authhead = "Authorization: ";
		//	authhead += std::string(dat->token_type);
		//	authhead += " ";
		//	authhead += std::string(dat->token);
		//	header = curl_slist_append( header, authhead.c_str() );
			
		//	if( dat->modhash != nullptr )
		//	{
		//		std::string modhash_header = "X-Modhash: ";
		//		modhash_header += std::string(dat->modhash);
		//		header = curl_slist_append( header, modhash_header.c_str() );
			//}
			
			//curl_get_sets(handle, "https://oauth.reddit.com/api/v1/me/blocked", header, dat->userAgent, jsondat);
			
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me/blocked" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L  );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &jsondat );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform( handle );
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			if( result != CURLE_OK)
			{
				set_curl_strerror(s, result);
				return s;
			} else {
				#ifdef DEBUG
				std::cout << jsondat << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("get_blocked_users_json.json");
				out << jsondat;
				#endif
				
				s.code = state;
				s.cstat = ERROR_NONE;
				s.message = "Test";
				return s;
				
				//auto j = nlohmann::json::parse(jsondat);
				
				/*try {
					std::string message = j.at("message");
					int scode = j.at("error");
					s.code = scode;
					s.message = message;
					s.cstat = ERROR_NONE;
					return s;
					
				} catch( nlohmann::json::out_of_range& ) {
					s.cstat = ERROR_NONE;
					s.message = "Error: Unable to get json data";
					return s;
				}*/
			}
		} else {
			set_curl_global_error(s);
			
			curl_easy_cleanup(handle);
			
			return s;
		}
	} else {
		set_curl_handle_error(s);
		
		return s;
	}
}

Status get_friends(AccessData* dat, std::vector< BasicUser* >* f)
{
	CURL *handle;
	CURLcode result;
	std::string jsondat;
	Status s;
	int state;
	
	handle = curl_easy_init();
	if( handle )
	{
		CURLcode glob = curl_global_init(CURL_GLOBAL_SSL);
		if(glob != CURLE_OK)
		{
			set_curl_global_error(s);
			
			return s;
		} else {
			struct curl_slist *header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me/friends" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &jsondat );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform( handle );
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state);
			s.code = state;
			
			if( result != CURLE_OK)
			{
				set_curl_strerror(s,result);
				return s;
				
			} else {
				
				#ifdef DEBUG
				std::cout << jsondat << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("get_friends_json.json");
				out << jsondat;
				#endif
				
				#ifdef DEBUG
				std::cout << jsondat.size() << std::endl;
				#endif
				
				if( jsondat.size() == 0)
				{
					s.cstat = ERROR_NONE;
					s.message = "No friends found";
					return s;
				}
				
				
				auto j = nlohmann::json::parse(jsondat);
		
				try {
				
					auto d = j.at("data");
					auto children = d.at("children");
					if( children.is_array() )
					{
						for( auto& elem : children )
						{
							auto k = nlohmann::json::parse( std::string(elem.dump()) );
							BasicUser* fr = new BasicUser;
							if(!fr) {
								bad_alloc_error(s);
								
								return s;
							}
							long date = k.at("date");
							std::string id = k.at("id");
							std::string name = k.at("name");
							
							fr->date = date;
							fr->id = id;
							fr->name = name;
							
							f->push_back(fr);
						}
						
						s.cstat = ERROR_NONE;
						s.message = "";
						return s;
						
					} else {
						not_an_array_error(s,"children");
						return s;
					}
				} catch ( nlohmann::json::out_of_range& e ) {
					try {
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						auto message = j.at("message");
						
						api_error(s,state,message);
						return s;
					} catch( nlohmann::json::out_of_range& e ){
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						unknown_error(s);
						
						return s;
					}
					
				}
				
			}
		}
	} else {
		set_curl_handle_error(s);
		return s;
	}
}


Status get_trophies( AccessData* dat, std::vector< Trophy *> *vt ) {
	CURL *handle;
	CURLcode result;
	std::string json;
	int state;
	Status s;
	
	handle = curl_easy_init();
	
	if( handle ) {
		CURLcode globalresult = curl_global_init(CURL_GLOBAL_SSL);
		if( globalresult != CURLE_OK )
		{
			set_curl_global_error(s);
			return s;
		} else {
			//struct curl_slist* header = nullptr;
			//curl_header_sets(header, dat);
			//curl_get_sets(handle, "https://oauth.reddit.com/api/v1/me/trophies", header, dat->userAgent, json);
			
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me/trophies" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L  );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state);
			s.code = state;
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s,result);
				return s;
			} else {
				
				//std::ofstream out("trophies.json");
				//out << json;
				
				//s.code = NULL;
				//s.cstat = ERROR_NONE;
				//s.message = "test";
				
				#ifdef DEBUG
				std::cout << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("get_trophies_json.json");
				out << json;
				#endif
				
				if( json.size() == 0 ) {
					s.cstat = ERROR_NONE;
					s.message = "Error: No trophies";
					return s;
				}
				
				auto j = nlohmann::json::parse(json);
				try {
					auto data = j.at("data");
					auto trophies = data.at("trophies");
					if( trophies.is_array() ) {
						for( auto& elem : trophies ) {
							try {
							
								auto tdata = elem.at("data");
								std::string award_id;
								try {
									award_id = tdata.at("award_id");
								} catch ( nlohmann::json::type_error& e ) {
									award_id = "";
								}
								
								std::string description;
								try {
									description = tdata.at("description");
								} catch ( nlohmann::json::type_error& e ) {
									description = "";
								}
								
								std::string icon_40 = tdata.at("icon_40");
								std::string icon_70 = tdata.at("icon_70");
								std::string name = tdata.at("name");
								
								std::string url;
								try {
									url = tdata.at("url");
								} catch( nlohmann::json::type_error& e ) {
									url = "";
								}
								
								std::string id;
								try {
									id = tdata.at("id");
								} catch ( nlohmann::json::type_error& e ) {
									id = "";
								}
								Trophy *t = new Trophy;
								if(!t){
									bad_alloc_error(s);
									return s;
								}
								t->award_id = award_id;
								t->description = description;
								t->icon40 = icon_40;
								t->icon70 = icon_70;
								t->id = id;
								t->name = name;
								t->kind = Award;
								
								vt->push_back(t);
							} catch ( nlohmann::json::out_of_range& e ) {
								array_error(s);
								return s;
							}
						
						}
						
					} else {
						not_an_array_error(s, "trophies");
					}
				} catch ( nlohmann::json::out_of_range& e ) {
					try {
					
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						std::string msg = j.at("message");

						api_error(s, state, msg);
						
						return s;
					} catch( nlohmann::json::out_of_range& e ) {
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						unknown_error(s);
						return s;
					}
				}
				
				s.cstat = ERROR_NONE;
				s.message = "";
				return s;
			}
		}
	} else {
		
		set_curl_handle_error(s);
		return s;
	}
}

Status get_prefs( AccessData* dat, UserPrefs* up ) {
	CURL *handle;
	CURLcode result;
	std::string json;
	int state;
	Status s;
	
	handle = curl_easy_init();
	
	if( handle ) {
		CURLcode glob_res = curl_global_init(CURL_GLOBAL_SSL);
		if( glob_res != CURLE_OK ) {
			set_curl_global_error(s);
			return s;
		} else {
			struct curl_slist* header;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me/prefs" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L  );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &state);
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK ) {
				
				set_curl_strerror(s,result);
				return s;
			} else if( result == CURLE_OK ) {
				
				#ifdef DEBUG
				std::cout << json << std::endl;
				std::cout << state << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("get_prefs_json.json");
				out << json;
				#endif
				
				auto j = nlohmann::json::parse(json);
				
				try {
					
					std::string accept_pms = j.at("accept_pms");
					bool allow_clicktracking = j.at("allow_clicktracking");
					bool beta = j.at("beta");
					bool clickgadget = j.at("clickgadget");
					bool compress = j.at("compress");
					auto content_langs = j.at("content_langs");
					if( content_langs.is_array() ) {
						for( auto& elem : content_langs ) {
							up->content_langs.push_back(elem);
						}
					} else {
						s.code = NULL;
						s.cstat = ERROR_JSONERROR;
						s.message = "Error: content_langs is not an array";
						return s;
					}
					bool creddit_autorenew = j.at("creddit_autorenew");
					std::string default_comment_sort = j.at("default_comment_sort");
					std::string default_theme_sr;
					try {
						default_theme_sr = j.at("default_theme_sr");
					} catch ( nlohmann::json::type_error& e ) {
						default_theme_sr = "";
					}
					bool domain_details = j.at("domain_details");
					bool email_digests = j.at("email_digests");
					bool email_messages = j.at("email_messages");
					
					bool enable_default_themes = j.at("enable_default_themes");
					std::string geopopular = j.at("geopopular");
					//bool hide_abusive_comments = j.at("hide_abusive_comments"); -- no longer exists for some reason
					bool hide_ads = j.at("hide_ads");
					bool hide_downs = j.at("hide_downs");
					bool hide_from_robots = j.at("hide_from_robots");
					bool hide_locationbar = j.at("hide_locationbar");
					bool hide_ups = j.at("hide_ups");
					bool highlight_controversial = j.at("highlight_controversial");
					bool highlight_new_comments = j.at("highlight_new_comments");
					
					bool ignore_suggested_sort = j.at("ignore_suggested_sort");
					bool label_nsfw = j.at("label_nsfw");
					std::string lang = j.at("lang");
					bool legacy_search = j.at("legacy_search");
					bool live_orangereds = j.at("live_orangereds");
					bool mark_messages_read = j.at("mark_messages_read");
					std::string media = j.at("media");
					std::string media_preview = j.at("media_preview");
					int min_comment_score = j.at("min_comment_score");
					int min_link_score = j.at("min_link_score");
					
					bool monitor_mentions = j.at("monitor_mentions");
					bool newwindow = j.at("newwindow");
					bool no_profanity = j.at("no_profanity");
					int num_comments = j.at("num_comments");
					int numsites = j.at("numsites");
					bool organic = j.at("organic");
					bool over_18 = j.at("over_18");
					bool private_feeds = j.at("private_feeds");
					bool public_votes = j.at("public_votes");
					bool research = j.at("research");
					
					bool search_include_over_18 = j.at("search_include_over_18");
					bool show_flair = j.at("show_flair");
					bool show_link_flair = j.at("show_link_flair");
					bool show_gold_expiration = j.at("show_gold_expiration");
					std::string show_promote;
					try {
						show_promote = j.at("show_promote");
					} catch( nlohmann::json::type_error& e ) {
						show_promote = "";
					}
					bool show_snoovatar = j.at("show_snoovatar");
					bool show_stylesheets = j.at("show_stylesheets");
					bool show_trending = j.at("show_trending");
					bool store_visits = j.at("store_visits");
					bool threaded_messages = j.at("threaded_messages");
					
					bool threaded_modmail = j.at("threaded_modmail");
					bool top_karma_subreddits = j.at("top_karma_subreddits");
					bool use_global_defaults = j.at("use_global_defaults");
					
					up->accept_pms = accept_pms;
					up->allow_clicktracking = allow_clicktracking;
					up->beta = beta;
					up->clickgadget = clickgadget;
					up->compress = compress;
					up->creddit_autorenew = creddit_autorenew;
					if( default_comment_sort == "confidence")
						up->default_comment_sort = Confidence;
					else if ( default_comment_sort == "old" )
						up->default_comment_sort = Old;
					if ( default_comment_sort == "top" )
						up->default_comment_sort = Top;
					else if ( default_comment_sort == "qa" )
						up->default_comment_sort = QA;
					if( default_comment_sort == "controversial" )
						up->default_comment_sort = Controversial;
					else if ( default_comment_sort == "new" )
						up->default_comment_sort = New;
					//up->default_comment_sort = default_comment_sort;
					up->default_theme_sr = default_theme_sr;
					up->domain_details = domain_details;
					up->email_digests = email_digests;
					up->email_messages = email_messages;
					
					up->enable_default_themes = enable_default_themes;
					up->geopopular = geopopular;
					//up->hide_abusive_comments = hide_abusive_comments; -- no longer exists 
					up->hide_ads = hide_ads;
					up->hide_downs = hide_downs;
					up->hide_from_robots = hide_from_robots;
					up->hide_locationbar = hide_locationbar;
					up->hide_ups = hide_ups;
					up->highlight_controversial = highlight_controversial;
					up->highlight_new_comments = highlight_new_comments;
					
					up->ignore_suggested_sort = ignore_suggested_sort;
					up->label_nsfw = label_nsfw;
					up->lang = lang;
					up->legacy_search = legacy_search;
					up->live_orangereds = live_orangereds;
					up->mark_messages_read = mark_messages_read;
					up->media = media;
					up->media_preview = media_preview;
					up->min_comment_score = min_comment_score;
					up->min_link_score = min_link_score;
					
					up->monitor_mentions = monitor_mentions;
					up->newwindow = newwindow;
					up->no_profanity = no_profanity;
					up->num_comments = num_comments;
					up->numsites = numsites;
					up->organic = organic;
					up->over_18 = over_18;
					up->private_feeds = private_feeds;
					up->public_votes = public_votes;
					up->research = research;
					
					up->search_include_over_18 = search_include_over_18;
					up->show_flair = show_flair;
					up->show_gold_expiration = show_gold_expiration;
					up->show_link_flair = show_link_flair;
					up->show_promote = show_promote;
					up->show_snoovatar = show_snoovatar;
					up->show_stylesheets = show_stylesheets;
					up->show_trending = show_trending;
					up->store_visits = store_visits;
					up->threaded_messages = threaded_messages;
					
					up->threaded_modmail = threaded_modmail;
					up->top_karma_subreddits = top_karma_subreddits;
					up->use_global_defaults = use_global_defaults;
					
					
				} catch ( nlohmann::json::out_of_range& e ) {
					try {
					
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						std::string message = j.at("message");
						int error = j.at("error");
						
						#ifdef DEBUG
						std::cerr << message << std::endl; 
						#endif
						
						api_error(s,error,message);
					} catch( nlohmann::json::out_of_range& e ) {
						
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						unknown_error(s);
						return s;
					}
				}
				
				s.cstat = ERROR_NONE;
				s.message = "";
				return s;
			}
		}
	} else {
		set_curl_handle_error(s);
		return s;
	}
}

Status get_blocked_prefs( AccessData* dat, std::vector< BasicUser* > *buv ) {
	CURL *handle;
	CURLcode result;
	std::string json;
	Status s;
	int state;
	
	handle = curl_easy_init();
	
	if( handle ) {
		CURLcode result = curl_global_init(CURL_GLOBAL_SSL);
		if( result != CURLE_OK ) {
			
			set_curl_global_error(s);
			return s;
		} else {
			struct curl_slist* header;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/prefs/blocked" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L  );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &state);
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK ) {
				
				set_curl_strerror(s,result);
				return s;
			} else {
				
				#ifdef DEBUG
				std::cout << json << std::endl;
				#endif
			
				#ifdef OUTJSON
				std::ofstream out("get_blocked_perfs_json.json");
				out << json;
				#endif
				
				//std::ofstream out("blocked_prefs.json");
				//out << json;
				
				auto j = nlohmann::json::parse(json);
				
				try {
					auto data = j.at("data");
					auto children = data.at("children");
					
					if( children.is_array() ) {
						for( auto& elem : children ) {
							long date = elem.at("date");
							std::string id = elem.at("id");
							std::string name = elem.at("name");
							
							BasicUser *bu = new BasicUser;
							if(!bu) {
								bad_alloc_error(s);
								return s;
							}
							
							bu->date = date;
							bu->id = id;
							bu->name = name;
							
							buv->push_back(bu);
						}
					} else {
						
						not_an_array_error(s, "children");
						return s; 
					}
				} catch (nlohmann::json::out_of_range& e){
					try {
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						std::string message = j.at("message");
						int error = j.at("error");
						
						#ifdef DEBUG
						std::cerr << message << std::endl;
						#endif
						
						api_error(s,error,message);
						return s;
					} catch ( nlohmann::json::out_of_range& e ) {
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						unknown_error(s);
						return s;
					}
				}
				
				s.cstat = ERROR_NONE;
				s.message = "";
				
				return s;
			}
		}
	} else {
		set_curl_handle_error(s);
		return s;
	}
	
}

Status get_trusted( AccessData* dat, std::vector< BasicUser* > *tuv ) {
	CURL *handle;
	CURLcode result;
	Status s;
	int state;
	std::string json;
	
	handle = curl_easy_init();
	
	if( handle ) {
		CURLcode global_result = curl_global_init(CURL_GLOBAL_SSL);
		if( global_result != CURLE_OK ) {
			set_curl_global_error(s);
			return s;
		} else if( global_result == CURLE_OK ){
			
			struct curl_slist* header;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/prefs/trusted" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L  );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &state);
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			
			if( result != CURLE_OK ) {
				set_curl_strerror(s,result);
				return s;
			} else {
				
				#ifdef DEBUG
				std::cerr << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("trusted_prefs.json");
				out << json;
				#endif
				
				auto j = nlohmann::json::parse(json);
				
				try {
					auto data = j.at("data");
					auto children = data.at("children");
					if( children.is_array() ) {
						
						for( auto& elem : children ) {
							std::string name = elem.at("name");
							std::string id = elem.at("id");
							long date = elem.at("date");
							
							BasicUser* up = new BasicUser;
							if(!up) {
								bad_alloc_error(s);
								return s;
							}
							
							up->name = name;
							up->id = id;
							up->date = date;
							
							tuv->push_back(up);
						}
					} else {
						not_an_array_error(s, "children");
						return s; 
					}
				} catch ( nlohmann::json::out_of_range& e) {
					try {
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						std::string message = j.at("message");
						
						#ifdef DEBUG
						std::cerr << message << std::endl;
						#endif
						
						int error = j.at("error");
						
						api_error(s, error, message);
						
						return s;
						
					} catch ( nlohmann::json::out_of_range& e ) {
						
						#ifdef DEBUG
						std::cout << e.what() << std::endl;
						#endif
						
						unknown_error(s);
						
						return s;
					}
				}
				
				return s;
			}
		}
	} else {
		set_curl_handle_error(s);
		return s;
	}
}

Status get_messagingprefs( AccessData* dat ) {
	CURL *handle;
	CURLcode result;
	std::string json;
	Status s;
	int state;
	
	handle = curl_easy_init();
	
	if( handle ) {
		CURLcode result = curl_global_init(CURL_GLOBAL_SSL);
		if( result != CURLE_OK ) {
			set_curl_global_error(s);
			return s;
		} else {
			struct curl_slist* header;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/prefs/messaging" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L  );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &state);
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK ) {
				
				set_curl_strerror(s,result);
				return s;
			} else {
				
				#ifdef DEBUG
				std::cout << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("messaging.json");
				out << json;
				#endif
				
				
				s.cstat = ERROR_NONE;
				s.message = "";
				return s;
			}
		}
	} else {
		set_curl_handle_error(s);
		return s;
	}
	
}
// not finished
Status patch_prefs( AccessData* dat, UserPrefs* up ) {
	Status s;
	int state;
	CURL *handle;
	CURLcode result;
	std::string json;

	
	handle = curl_easy_init();
	
	if( handle ) {
		if ( curl_global_init( CURL_GLOBAL_SSL ) != CURLE_OK ) {
			set_curl_global_error(s);
			return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			header = curl_slist_append( header, "Content-Type: application/json" );

			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me/prefs");
			curl_easy_setopt( handle, CURLOPT_CUSTOMREQUEST, "PATCH" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );

			
			std::string default_comment_sort;
			switch( up->default_comment_sort ) {
				case Confidence: default_comment_sort = "confidence"; break;
				case Old: default_comment_sort = "old"; break;
				case Top: default_comment_sort = "top"; break;
				case QA: default_comment_sort = "qa"; break;
				case Controversial: default_comment_sort = "controversial"; break;
				case New: default_comment_sort = "new"; break;
				default: default_comment_sort = "confidence"; break;
			}
			
			std::string gv;
			switch(up->g) {
				case GLOBAL: gv = str_tok(GLOBAL); break; case US: gv = str_tok(US); break; case AU: gv = str_tok(AU); break;
				case BG: gv = str_tok(BG); break; case CA: gv = str_tok(CA); break; case CL: gv = str_tok(CL); break;
				case CO: gv = str_tok(CO); break; case HR: gv = str_tok(HR); break; case CZ: gv = str_tok(CZ); break;
			}
			std::string inputjson;
			nlohmann::json postjson = {
				{ "allow_clicktracking", up->allow_clicktracking },
				{ "num_comments", up->num_comments },
				{ "beta", up->beta },
				{ "clickgadget", up->clickgadget },
				{ "compress", up->clickgadget },
				{ "creddit_autorenew", up->creddit_autorenew },
				{ "default_comment_sort", default_comment_sort },
				{ "domain_details", up->domain_details },
				{ "email_digests", up->email_digests },
				{ "enable_default_themes", up->enable_default_themes },
				//{ "g", str_tok(up->g) },
				{ "hide_ads", up->hide_ads }
			};
			//std::cout << std::setw(4) << postjson;
			
			inputjson = postjson.dump();
			//inputjson = "{ \"num_comments\" : 500 }";
			//std::cout << inputjson << std::endl;
			
			curl_easy_setopt( handle, CURLOPT_POSTFIELDS, inputjson.c_str() );
			//curl_easy_setopt( handle, CURLOPT_RETURNTRANSFER, 1 );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			if( result != CURLE_OK ) {
				set_curl_strerror(s,result);
				return s;
			} else {
				
				#ifdef DEBUG
				std::cout << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("patch_prefs_json.json");
				out << json;
				#endif
				
				if( json.size() == 0)
					json = "";
					
				auto j = nlohmann::json::parse(json);
				try {
					
					std::string message = j.at("message");
					int error = j.at("error");
					
					api_error(s, error, message);
					return s;
				} catch ( nlohmann::json::out_of_range& e ) {
					#ifdef DEBUG
					std::cout << e.what() << std::endl;
					#endif
					unknown_error(s);
					return s;
				}
				return s;
			}
			
		}
	} else {
		set_curl_handle_error(s);
		return s;
	}
}
