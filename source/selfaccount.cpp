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
				int commentkarma;
				int inbox_count;
				int link_karma;
				int gold_creddits;
				
				long created;
				long created_utc;
				
				std::string modhash;
				std::string name;
				std::string id;
				
				bool has_mail;
				bool has_mod_mail;
				bool has_verified_email;
				bool is_gold;
				bool is_mod;
				bool in_beta;
				bool is_suspended;
				bool over_18;
				bool is_employee;
				bool is_sponsor;
				bool is_friend;
				
				#ifdef DEBUG
				std::cout << returndata << std::endl;
				#endif
				
				auto j = nlohmann::json::parse(returndata);

				
				try {
					commentkarma = j.at("comment_karma");
					link_karma = j.at("link_karma");

					created = j.at("created");
					created_utc = j.at("created_utc");
	
					name = j.at("name");
					id = j.at("id");

					inbox_count = j.at("inbox_count");
	
					has_mail = j.at("has_mail");
					has_mod_mail = j.at("has_mod_mail");
					has_verified_email = j.at("has_verified_email");

					is_sponsor = j.at("is_sponsor");
					is_employee = j.at("is_employee");
					is_suspended = j.at("is_suspended");
					is_gold = j.at("is_gold");
					in_beta = j.at("in_beta");
					is_mod = j.at("is_mod");
					over_18 = j.at("over_18");
					is_friend = j.at("is_friend");
				} catch( nlohmann::json::out_of_range& e ) {
					try {
						std::string message = j.at("message");
						
						api_error(st, status_code, message);
						return st;
					} catch ( nlohmann::json::out_of_range& e ) {
						unknown_error(st);
						return st;
					}
				}
				
				try {
					modhash = j.at("modhash");
				} catch(nlohmann::json::type_error& e ){
					modhash = "0";
				}
				
				//person = new Self;
				person->CommentKarma = commentkarma;
				person->inbox_count = inbox_count;
				person->LinkKarma = link_karma;
				// Modhash conversion
				if(modhash != "0")
				{
					char* cmodhash;
					std::strcpy(cmodhash, modhash.c_str());
					person->modhash = cmodhash;
				} else {
					person->modhash = nullptr;
				}
				//end
				person->name = name;
				person->user_id = id;
				
				
				person->has_mail = has_mail;
				person->has_mod_mail = has_mod_mail;
				person->has_verified_email = has_verified_email;
				
				person->is_sponsor = is_sponsor;
				person->is_suspended = is_suspended;
				person->is_employee = is_employee;
				person->in_beta = in_beta;
				person->is_gold = is_gold;
				person->is_mod = is_mod;
				person->over_18 = over_18;
				person->is_friend = is_friend;
				person->created = created;
				person->created_utc = created_utc;
				
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
						std::string message;
						int error;
							
						message = j.at("message");
						error = j.at("error");
							
						api_error(s, error, message);
							
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
			/*std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			header = curl_slist_append( header, authhead.c_str() );
			
			if( dat->modhash != nullptr )
			{
				std::string modhash_header = "X-Modhash: ";
				modhash_header += std::string(dat->modhash);
				header = curl_slist_append( header, modhash_header.c_str() );
			}*/
			
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
				std::ofstream out("blocked.json");
				out << jsondat;
				
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
						auto message = j.at("message");
						
						api_error(s,state,message);
						return s;
					} catch( nlohmann::json::out_of_range& e ){
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
				
				/*std::ofstream out("trophies.json");
				out << json;
				
				s.code = NULL;
				s.cstat = ERROR_NONE;
				s.message = "test";*/
				
				#ifdef DEBUG
				std::cout << json << std::endl;
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
					
						std::string msg = j.at("message");

						api_error(s, state, msg);
						
						return s;
					} catch( nlohmann::json::out_of_range& e ) {
						
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
					bool hide_abusive_comments = j.at("hide_abusive_comments");
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
					up->default_comment_sort = default_comment_sort;
					up->default_theme_sr = default_theme_sr;
					up->domain_details = domain_details;
					up->email_digests = email_digests;
					up->email_messages = email_messages;
					
					up->enable_default_themes = enable_default_themes;
					up->geopopular = geopopular;
					up->hide_abusive_comments = hide_abusive_comments;
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
					
						std::string message = j.at("message");
						int error = j.at("error");
						
						
						#ifdef DEBUG
						std::cerr << message << std::endl; 
						#endif
						
						api_error(s,error,message);
					} catch( nlohmann::json::out_of_range& e ) {
						
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
			#ifdef DEBUG
			std::cerr << "Error: Failed to initialize CURL GLOBAL" << std::endl;
			#endif
			
			s.code = NULL;
			s.cstat = ERROR_CURL_GLOBAL_FAILED_INIT;
			s.message = "Error: Failed to initialize CURL GLOBAL";
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
						std::string message = j.at("message");
						int error = j.at("error");
						
						#ifdef DEBUG
						std::cerr << message << std::endl;
						#endif
						
						api_error(s,error,message);
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
		#ifdef DEBUG
		std::cerr << "Error: Failed to initialize CURL * handle";
		#endif
		
		s.code = NULL;
		s.cstat = ERROR_CURL_HANDLE_FAILED_INIT;
		s.message = "Error: Failed to initialize CURL * handle";
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
				
				//std::ofstream out("trusted_prefs.json");
				//out << json;
				
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
						
						std::string message = j.at("message");
						
						#ifdef DEBUG
						std::cerr << message << std::endl;
						#endif
						
						int error = j.at("error");
						
						api_error(s, error, message);
						
						return s;
						
					} catch ( nlohmann::json::out_of_range& e ) {
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
				std::ofstream out("messaging.json");
				out << json;
				
				
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
