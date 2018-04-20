#include "subreddit/sub/linkncomms.hpp"
#include <iostream>
#include <fstream>

Status get_trending( AccessData* acd )
{
	Status s;
	std::string json;
	int state;
	
	CURL* handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle ) {
		if ( curl_global_init(CURL_GLOBAL_SSL) != CURLE_OK ) {
			set_curl_global_error(s); return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(acd->token_type);
			authhead += std::string(acd->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/trending_subreddits");
			curl_easy_setopt( handle, CURLOPT_USERAGENT, acd->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s,result); return s;
			} else {
				
				#ifdef DEBUG || _DEBUG
				std::cout << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("get_trending.json");
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


Status get_id_by_name( AccessData* dat, std::vector< std::string > names )
{
	Status s;
	std::string json;
	int state;
	
	CURL* handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle )
	{
		if( curl_global_init( CURL_GLOBAL_SSL) != CURLE_OK )
		{
			set_curl_global_error(s); return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			std::string url = "https://oauth.reddit.com/by_id/";
			for( int i = 0; i < names.size(); i++ )
			{
				url += names[i];
				if( !(i == names.size()) )
				{
					url += ",";
				}
			}
			
			curl_easy_setopt( handle, CURLOPT_URL, url.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s,result); return s;
			} else {
				
				#ifdef DEBUG || _DEBUG
				std::cout << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("get_id_by_name.json");
				out << json;
				#endif
				
				s.cstat = ERROR_NONE;
				s.message = "";
				
				return s;
				
			}
			
		}
	} else {
		set_curl_handle_error(s); return s;
	}
}

/********* LINKS AND COMMENTS *************/
Status comment( AccessData* dat, std::string parent, std::string text )
{
	Status s;
	int state;
	std::string json;
	
	CURL *handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle )
	{
		CURLcode gr = curl_global_init( CURL_GLOBAL_SSL );
		if( gr != CURLE_OK )
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
			
			nlohmann::json j = {
				{ "api_type", "json" },
				{ "parent", parent },
				{ "scope", "submit" },
				{ "text", text }
			};
			std::string jdata = j.dump();
			curl_easy_setopt( handle, CURLOPT_URL, "https://oauth.reddit.com/api/comment" );
			curl_easy_setopt( handle, CURLOPT_POST, 1L );
			curl_easy_setopt( handle, CURLOPT_POSTFIELDS, jdata.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s, result);
				return s;
			} else {
				#ifdef DEBUG || _DEBUG
				std::cout << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("comments.json");
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

Status delete_comment( AccessData* dat, std::string fullname )
{
	Status s;
	int state;
	std::string json;
	
	CURL *handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle )
	{
		CURLcode gres = curl_global_init( CURL_GLOBAL_SSL );
		if( gres != CURLE_OK )
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
			
			std::string url = "https://oauth.reddit.com/api/del?id=";
			url += fullname;
			
			curl_easy_setopt( handle, CURLOPT_URL, url.c_str() );
			curl_easy_setopt( handle, CURLOPT_POST, 1L );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			
			#ifdef DEBUG || _DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state ); s.code = state;
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s,result); return s;
			} else {
				#ifdef OUTJSON
				std::ofstream out("delete_comment.json");
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

Status edit_user_comment( AccessData* dat, std::string text, std::string id )
{
	Status s;
	int state;
	std::string json;
	
	CURL *handle;
	CURLcode result;
	
	handle = curl_easy_init();
	
	if( handle )
	{
		CURLcode gobres = curl_global_init(CURL_GLOBAL_SSL);
		if( gobres != CURLE_OK )
		{
			set_curl_global_error(s); return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			std::string url = "https://oauth.reddit.com/api/editusertext";
			
			
			/*	PARAMS	*/
			// Needs work
			nlohmann::json params = {
				/*{ "api_type", "json" },
				{ "richtext_json", [{ "return_rtjson", true },{"text", text.c_str()}] },
				{ "thing_id", id.c_str() }*/
			};
			std::string string_params = params.dump();
			curl_easy_setopt( handle, CURLOPT_URL, url.c_str() );
			curl_easy_setopt( handle, CURLOPT_POST, 1L );
			curl_easy_setopt( handle, CURLOPT_POSTFIELDS, string_params.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			
			result = curl_easy_perform(handle);
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			curl_global_cleanup();
			curl_easy_cleanup(handle);
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s,result); return s;
			} else {
				
				#ifdef OUTJSON
				std::ofstream out("edit_user_comment.json");
				out << json;
				#endif
				
				std::cout << json << std::endl;
				
				s.cstat = ERROR_NONE;
				s.message = "";
				
				return s;
			}
			
			
		}
	} else {
		set_curl_handle_error(s); return s;
	}
}
