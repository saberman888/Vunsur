#include "include/gold/gold.hpp"

Status gild( AccessData* acd, std::string fullname )
{
	Status s;
	int state;
	return s;
}

Status give_gold( AccessData* dat, std::string username )
{
	Status s;
	int state;
	CURL* handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle ) {
		CURLcode glob_res = curl_global_init(CURL_GLOBAL_SSL);
		if( glob_res != CURLE_OK ) {
			set_curl_global_error(s);
			return s;
		} else {
			
			std::string url = "https://oauth.reddit.com/api/v1/gold/give";
			url += username;
			
			struct curl_slist* header;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			curl_easy_setopt( handle, CURLOPT_POST, 1L);
			curl_easy_setopt( handle, CURLOPT_URL, url.c_str() );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			if( result != CURLE_OK ) {
				set_curl_strerror(s,result);
				return s;
			} else {
				return s;
			}
			
		}
	} else {
		set_curl_handle_error(s);
		return s;
	}
}
