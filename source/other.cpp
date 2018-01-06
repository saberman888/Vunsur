#include "other.hpp"
#include <iostream>
#include <fstream>

Status scopes( AccessData* dat )
{
	Status s;
	int state;
	std::string json;
	CURL *handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle )
	{
		if( curl_global_init(CURL_GLOBAL_SSL) != CURLE_OK )
		{
			set_curl_global_error(s);
			return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			curl_easy_setopt( handle , CURLOPT_URL, "https://oauth.reddit.com/api/v1/scopes ");
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			
			result = curl_easy_perform( handle );
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s,result);
				return s;
			} else {
				#ifdef DEBUG
				std::cout << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out( "scopes.json" );
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
