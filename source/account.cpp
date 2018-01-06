#include "account/account.hpp"
#include <iostream>

Status get_self(AccessData* dat, std::string userAgent, Self * person)
{
	CURL * handle;
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
			std::string authheader  = "Authorization: ";
			authheader += dat->token_type;
			authheader += " ";
			authheader += dat->token;
			
			header = curl_slist_append( header, authheader.c_str() );
			
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L  );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, userAgent.c_str() );
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
				#ifdef DEBUG
				std::cerr << "curl_easy_strerror(): " << curl_easy_strerror(result) << std::endl;
				#endif
				
				st.cstat = ERROR_CURL_STRERROR;
				st.code = NULL;
				st.message = curl_easy_strerror(result);
				
				return st;
			} else {
				int commentkarma;
				int inbox_count;
				int link_karma;
				int gold_creddits;
				
				float created;
				float created_utc;
				
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
				} catch( nlohmann::json::out_of_range& e ) {
					try {
						std::string message = j.at("message");
						
						st.code = status_code;
						st.cstat = ERROR_NONE;
						st.message = message;
						return st;
					} catch ( nlohmann::json::out_of_range& e ) {
						st.message = "Error: Unknown Error";
						st.cstat = ERROR_NONE;
						st.code = status_code;
						return st;
					}
				}
				
				try {
					modhash = j.at("modhash");
				} catch(nlohmann::json::out_of_range& e ){
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
				
				person->created = created;
				person->created_utc = created_utc;
				
				st.code = status_code;
				st.cstat = ERROR_NONE;
				st.message = "";
				
				return st;
			}
		} else {
			#ifdef DEBUG
			std::cerr << "Error: Failed to initialize CURL GLOBAL" << std::endl;
			#endif
			
			curl_easy_cleanup(handle);
			st.code = NULL;
			st.cstat = ERROR_CURL_GLOBAL_FAILED_INIT;
			st.message = "Error: Failed to initialize CURL GLOBAL";
			return st;
		}
	} else {
		#ifdef DEBUG
		std::cerr << "Error: Failed to initialize CURL * handle " << std::endl;
		#endif
		
		st.code = NULL;
		st.cstat = ERROR_CURL_HANDLE_FAILED_INIT;
		st.message = "Error: Failed to initialize CURL * handle";
		
		return st;
	}
}


void get_blocked_users(AccessData* dat, std::string userAgent)
{
	CURL * handle;
	CURLcode result;
	std::string jsondat;
	
	handle = curl_easy_init();
	
	if(handle)
	{
		CURLcode globalRes = curl_global_init(CURL_GLOBAL_SSL);
		if(globalRes == CURLE_OK)
		{
			curl_slist *header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += dat->token_type;
			authhead += " ";
			authhead += dat->token;
			header = curl_slist_append( header, authhead.c_str() );
			
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me/blocked" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, userAgent );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &jsondat );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform( handle );
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			if( result != CURLE_OK)
			{
				std::cerr << "curl_easy_strerror(): " << curl_easy_strerror(result) << std::endl;
			} else {
				std::ofstream out("blocked.json");
				out << jsondat;
				
				auto j = nlohmann::json::parse(jsondat);
				
				
				// Error
				std::string message;
				int error;
				try {
					message = j.at("message");
					error = j.at("error");
					
					std::cout << "Error: " << error << " " << message << std::endl;
				} catch( nlohmann::json::out_of_range& ) {
					
				}
			}
		} else {
			std::cerr << "Error: Failed to initialize CURL GLOBAL" << std::endl;
			curl_easy_cleanup(handle);
		}
	} else {
		std::cerr << "Error: Failed to initialize CURL * handle" << std::endl;
	}
}

std::vector< Friend* > get_friends(AccessData* dat, std::string userAgent)
{
	CURL * handle;
	CURLcode result;
	std::string jsondat;
	std::vector< Friend* > collectedFriends;
	
	handle = curl_easy_init();
	if( handle )
	{
		CURLcode glob = curl_global_init(CURL_GLOBAL_SSL);
		if(glob != CURLE_OK)
		{
			std::cerr << "Error: Failed to initialize CURL GLOBAL" << std::endl;
		} else {
			curl_slist *header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += dat->token_type;
			authhead += " ";
			authhead += dat->token;
			header = curl_slist_append( header, authhead.c_str() );
			
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/v1/me/friends" );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, userAgent );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &jsondat );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform( handle );
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			#ifdef DEBUG
			std::cout << jsondat << std::endl;
			#endif
			
			if( result != CURLE_OK)
			{
				std::cerr << "curl_easy_strerror(): " << curl_easy_strerror(result) << std::endl;
				return collectedFriends;
			} else {
				auto j = nlohmann::json::parse(jsondat);
				
				auto d = j.at("data");
				auto children = d.at("children");
				if( d.is_array() )
				{
					/*for( auto it = d.begin(); it != d.end(); it++)
					{
						Friend* f = new Friend;
						if(!f)
						{
							std::cerr << "Error: Bad allocation " << std::endl;
							return collectedFriends;
						}
						std::cout << it.key << std::endl;
						#ifdef DEBUG
						std::cout << name << std::endl;
						#endif
						//f->name = name;
						collectedFriends.push_back(f);
					}*/
					return collectedFriends;
				}
				
			}
		}
	} else {
		std::cerr << "Error: Failed to initialize CURL * handle" << std::endl;
		return collectedFriends;
	}
}
