#include "include/account/user.hpp"
#include <iostream>
Status aboutUser( AccessData* acd, std::string username, UserAccount* ua )
{
	// declare the main variables we need
	CURL *handle; // The handle we need to perform curl operations
	CURLcode result; // result variable to check if it was successful
	std::string jsondata; // where we will store jsondata
	Status s; // Our status variable
	// initialize handle
	handle = curl_easy_init();
	// Check if handle initialized failed or not
	if( handle ) {
		CURLcode globalRes = curl_global_init(CURL_GLOBAL_SSL);
		if( globalRes == CURLE_OK ) {
			
			std::string authheader = "Authorization: ";
			authheader += acd->token_type;
			authheader += " ";
			authheader += acd->token;
			
			curl_slist *header = nullptr;
			curl_slist_append(header, authheader.c_str() );
			
			std::string url = "https://oauth.reddit.com/api/v1/user/";
			url += std::string(username);
			url += "/overview";
			
			curl_easy_setopt( handle, CURLOPT_URL, url.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, acd->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &jsondata );
			
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform( handle );
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &s.code );
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s, result);
				return s;
			} else {
				#ifdef DEBUG
				std::cout << jsondata << std::endl;
				#endif
				
				std::ofstream out("about.json");
				out << jsondata;
				
				s.cstat = ERROR_NONE;
				s.message = "";
				
				return s;
			}
		} else {
			// If curl_global fails then continue here
			set_curl_global_error(s);
			
			return s;
		}
	} else {
		// If curl *handle failes to initialize it continues here
		set_curl_handle_error(s);
		return s;
	}
	
}
