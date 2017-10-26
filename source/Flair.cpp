#include "include/flair/Flair.hpp"
#include <iostream>

Status clear_flair_templates( AccessData* dat, std::string subreddit, FlairType ft )
{
	Status s;
	int state;
	CURL *handle;
	CURLcode result;
	std::string json;
	
	handle = curl_easy_init();
	
	if( handle ) {
		CURLcode gresult = curl_global_init(CURL_GLOBAL_SSL);
		if( gresult != CURLE_OK ) {
			set_curl_global_error(s);
			return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			std::string modhash = "X-Modhash: ";
			modhash += std::string(dat->modhash);
			
			header = curl_slist_append( header, modhash.c_str() );
			
			std::string URL = "https://oauth.reddit.com/api/v1/";
			URL += subreddit;
			URL += "/api/clearflairtemplates";
			
			curl_easy_setopt( handle, CURLOPT_URL, URL.c_str() );
			curl_easy_setopt( handle, CURLOPT_POST, 1L );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			
			std::string flair_type;
			switch( ft ) {
				case USER_FLAIR: flair_type = "USER_FLAIR";
				case LINK_FLAIR: flair_type = "LINK_FLAIR";
				default: flair_type = "";
			}
			nlohmann::json pd = {
				{ "api_type", "json" },
				{ "flair_type", flair_type }
			};
			
			curl_easy_setopt( handle, CURLOPT_POSTFIELDS, pd.dump() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK ) {
				set_curl_strerror(s, result);
				return s;
			} else {
				if( json.size() == 0 )
					json = "";
				#ifdef DEBUG
				std::cout << json << std::endl;
				#endif
				
				//std::ofstream out("clearflairtemplate.json");
				//out << json;
				
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