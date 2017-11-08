#include "include/subreddit/subreddit.hpp"
#include <iostream>
#include <fstream>

Status subreddit_about( AccessData* acd, std::string subreddit )
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

