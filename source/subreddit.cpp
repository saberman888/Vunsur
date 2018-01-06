#include "subreddit/sub/subreddit.hpp"
#include <iostream>
#include <fstream>

Status subreddit_about( AccessData* acd, std::string subreddit, SubredditInfo* subi )
{
	Status s;
	int state;
	std::string json;
	CURL *handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle ) {
		CURLcode gres = curl_global_init(CURL_GLOBAL_SSL);
		if( gres != CURLE_OK ) {
			set_curl_global_error(s);
			return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(acd->token_type);
			authhead += " ";
			authhead += std::string(acd->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			std::string url = "https://oauth.reddit.com/r/";
			url += subreddit;
			url += "/about/";
			
			
			curl_easy_setopt( handle, CURLOPT_URL, url.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, acd->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK ) {
				set_curl_strerror(s,result);
				return s;
			} else {
				#ifdef OUTJSON
				std::ofstream out("subreddit_about_banned.json");
				out << json;
				#endif
				
				nlohmann::json j = nlohmann::json::parse(json);
				try {
				
					nlohmann::json data = j.at("data");
					// since this is obviously a subreddit it's kind is labeled Subreddit
					subi->kind = Subreddit;
					
					subi->accounts_active = data.at("accounts_active");
					subi->accounts_active_is_fuzzed = data.at("accounts_active_is_fuzzed");
					
					nlohmann::json advertiser_category;
					
					advertiser_category = data.at("advertiser_category");
					if( advertiser_category.is_null() ) {
						subi->advertiser_category = "";
					} else {
						subi->advertiser_category = data.at("advertiser_category");
					}
					
					subi->allow_discovery = data.at("allow_discovery");
					subi->allow_images = data.at("allow_images");
					
					/*
					
						The Json values in allow_videos and allow_videogifs
						are in beta. In non-opted communities these values
						do not appear, so when they aren't present the api
						assigns false to these values 
						
					*/
					
					try {
						bool allow_videos = data.at("allow_videos");
						
						subi->allow_videos = allow_videos;
					} catch ( nlohmann::json::out_of_range& e ) {
						subi->allow_videos = false;
					}
					
					
					try {
						bool allow_videogifs = data.at("allow_videogifs");
						subi->allow_videogifs = allow_videogifs;
					} catch ( nlohmann::json::out_of_range& e ) {
						subi->allow_videogifs = false;
					}
					
					//subi->allow_videos = data.at("allow_videos");
					//subi->allow_videogifs = data.at("allow_videogifs");
					
					subi->audience_target = data.at("audience_target");
					
					nlohmann::json banner_img = data.at("banner_img");
					if( !banner_img.is_null() ) {
						subi->banner_img = data.at("banner_img");
					} else {
						subi->banner_img = "";
					}
					
					nlohmann::json banner_size;
					banner_size = data.at("banner_size");
					
					if( !banner_size.is_null() ) {
						
						for( auto& elem : banner_size ) {
							subi->banner_size.push_back(elem);
						}
					}
					
					subi->collapse_deleted_comments = data.at("collapse_deleted_comments");
					subi->comment_score_hide_mins = data.at("comment_score_hide_mins");
					subi->created = data.at("created");
					subi->created_utc = data.at("created_utc");
					subi->description = data.at("description");
					
					nlohmann::json description_html = data.at("description_html");
					if( !description_html.is_null() ) {
						subi->description_html = data.at("description_html");
					} else {
						subi->description_html = "";
					}
					subi->display_name = data.at("display_name");
					subi->display_name_prefixed = data.at("display_name_prefixed");
					
					nlohmann::json header_img = data.at("header_img");
					if( !header_img.is_null() ) {
						subi->header_img = data.at("header_img");
					} else {
						subi->header_img = "";
					}
					
					nlohmann::json header_size;
					header_size = data.at("header_size");
					if( !header_size.is_null() ) {
						for( auto& elem : header_size ) {
							subi->header_size.push_back(elem);
						}	
					}
					
					nlohmann::json header_title = data.at("header_title");
					if( !header_title.is_null() ) {
						subi->header_title = data.at("header_title");
					} else {
						subi->header_title = "";
					}
					
					subi->hide_ads = data.at("hide_ads");
					
					nlohmann::json icon_img = data.at("icon_img");
					if( !icon_img.is_null() ) {
						subi->icon_img = data.at("icon_img");
					} else {
						subi->icon_img = "";
					}
					
					nlohmann::json icon_size;
					icon_size = data.at("icon_size");
					
					if( !icon_size.is_null() ) {
						for( auto& elem : icon_size ) {
							subi->icon_size.push_back(elem);
						}
					}
					
					subi->id = data.at("id");
					try {
					
						nlohmann::json is_enrolled_in_new_modmail;
						
						is_enrolled_in_new_modmail = data.at("is_enrolled_in_new_modmail");
						if( !is_enrolled_in_new_modmail.is_null() ) {
							subi->is_enrolled_in_new_modmail = data.at("is_enrolled_in_modmail");
						} else {
							subi->is_enrolled_in_new_modmail = false;
						}
					} catch ( nlohmann::json::out_of_range& e ) {
						subi->is_enrolled_in_new_modmail = false;
					}
					
					subi->key_color = data.at("key_color");
					subi->lang = data.at("lang");
					subi->link_flair_enabled = data.at("link_flair_enabled");
					subi->name = data.at("name");
					subi->over18 = data.at("over18");
					subi->public_description = data.at("public_description");
					
					nlohmann::json public_description_html = data.at("public_description_html");
					if( !public_description_html.is_null() ) {
						subi->public_description_html = data.at("public_description_html");
					} else {
						subi->public_description_html = "";
					}
					
					//subi->public_description_html = data.at("public_description_html");
					subi->public_traffic = data.at("public_traffic");
					subi->quarantine = data.at("quarantine");
					subi->show_media = data.at("show_media");
					subi->show_media_preview = data.at("show_media_preview");
					subi->spoilers_enabled = data.at("spoilers_enabled");
					subi->submission_type = data.at("submission_type");
					
					nlohmann::json submit_link_label = data.at("submit_link_label");
					if ( !submit_link_label.is_null() ) {
						subi->submit_link_label = data.at("submit_link_label");
					} else {
						subi->submit_link_label = "";
					}
					subi->submit_text = data.at("submit_text");
					
					nlohmann::json submit_text_html;
					submit_text_html = data.at("submit_text_html");
					if( !submit_text_html.is_null() ) {
						subi->submit_text_html = data.at("submit_text_html");
					} else {
						subi->submit_text_html = "";
					}
					
					nlohmann::json submit_text_label = data.at("submit_text_label");
					if( !submit_text_label.is_null() ) {
						subi->submit_text_label = data.at("submit_text_label");
					} else {
						subi->submit_text_label = "";
					}
					
					subi->subreddit_type = data.at("subreddit_type");
					subi->subscribers = data.at("subscribers");
					
					nlohmann::json suggested_comment_sort;
					suggested_comment_sort = data.at("suggested_comment_sort");
					
					if( !suggested_comment_sort.is_null() ) {
						SortType dst = determineSortType(data.at("suggested_comment_sort"));
						subi->suggested_comment_sort = dst;
					} else {
						subi->suggested_comment_sort = None;
					}
					
					subi->title = data.at("title");
					subi->url = data.at("url");
					
					nlohmann::json user_can_flair_in_sr = data.at("user_can_flair_in_sr");
					if( !user_can_flair_in_sr.is_null() ) {
						subi->user_can_flair_in_sr = data.at("user_can_flair_in_sr");
					} else {
						subi->user_can_flair_in_sr = false;
					}
					
					
					nlohmann::json user_flair_css_class = data.at("user_flair_css_class");
					if( !user_flair_css_class.is_null() ) {
						subi->user_flair_css_class = data.at("user_flair_css_class");
					} else {
						subi->user_flair_css_class = "";
					}
					
					subi->user_flair_enabled_in_sr = data.at("user_flair_enabled_in_sr");
					
					nlohmann::json user_flair_text = data.at("user_flair_text");
					if( !user_flair_text.is_null() ) {
						subi->user_flair_text = data.at("user_flair_text");
					} else {
						subi->user_flair_text = "";
					}
					
					subi->user_has_favorited = data.at("user_has_favorited");
					subi->user_is_banned = data.at("user_is_banned");
					subi->user_is_contributor = data.at("user_is_contributor");
					subi->user_is_moderator = data.at("user_is_moderator");
					subi->user_is_muted = data.at("user_is_muted");
					subi->user_is_subscriber = data.at("user_is_subscriber");
					subi->user_sr_flair_enabled = data.at("user_sr_flair_enabled");
					subi->user_sr_theme_enabled = data.at("user_sr_theme_enabled");
					
					nlohmann::json whitelist_status = data.at("whitelist_status");
					if( !whitelist_status.is_null() ) {
						subi->whitelist_status = data.at("whitelist_status");
					} else {
						subi->whitelist_status = "";
					}
					
					nlohmann::json wiki_enabled = data.at("wiki_enabled");
					if( !wiki_enabled.is_null() ) {
						subi->wiki_enabled = data.at("wiki_enabled");
					} else {
						subi->wiki_enabled = false;
					}
					
					
					
				} catch ( nlohmann::json::out_of_range& e ) {
					try {
					
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						
						std::string message = j.at("message");
						api_error(s,state,message);
						
						return s;
					} catch ( nlohmann::json::out_of_range& e ) {
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

Status subreddit_about_edit( AccessData* acd, std::string subreddit )
{
	Status s;
	int state;
	std::string json;
	CURL* handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle ) {
		if( curl_global_init( CURL_GLOBAL_SSL ) != CURLE_OK ) {
			set_curl_global_error(s);
			return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(acd->token_type);
			authhead += " ";
			authhead += std::string(acd->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			std::string url = "https://oauth.reddit.com/r/";
			url += subreddit;
			url += "/about/edit/";
			
			
			curl_easy_setopt( handle, CURLOPT_URL, url.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, acd->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK ) {
				set_curl_strerror(s,result);
				return s;
			} else {
				s.code = state;
				
				#ifdef OUTJSON
				std::ofstream out("subreddit_about_edit.json");
				out << json;
				#endif
				
				nlohmann::json j = nlohmann::json::parse(json);
				
				try {
					
				} catch ( nlohmann::json::out_of_range& e ) {
					try {
					
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
						#endif
						std::string message = j.at("message");
						api_error(s,state,message);
						return s;
					} catch ( nlohmann::json::out_of_range& e ) {
						#ifdef DEBUG
						std::cerr << e.what() << std::endl;
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

