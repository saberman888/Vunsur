#include "subreddit/sub/flair/Flair.hpp"
#include <iostream>
#include <fstream>

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
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			//std::string modhash = "X-Modhash: ";
			//modhash += std::string(dat->modhash);
			
			//header = curl_slist_append( header, modhash.c_str() );
			
			std::string URL = "https://oauth.reddit.com/r/";
			URL += subreddit;
			URL += "/api/clearflairtemplates";
			
			curl_easy_setopt( handle, CURLOPT_URL, URL.c_str() );
			curl_easy_setopt( handle, CURLOPT_POST, 1L );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			
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
			
			#ifdef DEBUG || _DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK ) {
				set_curl_strerror(s, result);
				return s;
			} else {
				if( json.size() == 0 )
					json = "";
				#ifdef DEBUG || _DEBUG
				std::cout << json << std::endl;
				#endif
				
				#ifdef OUTJSON
				std::ofstream out("clearflairtemplate.json");
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


Status delete_flair( AccessData* dat, std::string subreddit, std::string flair_template_name )
{
	Status s;
	int state;
	CURL *handle;
	CURLcode result;
	std::string json;
	
	handle = curl_easy_init();
	
	if( handle )
	{
		CURLcode gresult = curl_global_init(CURL_GLOBAL_SSL);
		if( gresult != CURLE_OK ) {
			set_curl_global_error(s); return s;
		} else {
			struct curl_slist* header = nullptr;
			std::string authhead = "Authorization: ";
			authhead += std::string(dat->token_type);
			authhead += " ";
			authhead += std::string(dat->token);
			
			header = curl_slist_append( header, authhead.c_str() );
			
			std::string URL = "https://oauth.reddit.com/r/";
			URL += subreddit;
			URL += "/api/deleteflair";
			
			nlohmann::json postdata = {
				{ "api_type", "json" },
				{ "name", flair_template_name }
			};
			
			std::string stringjson = postdata.dump();
			
			curl_easy_setopt( handle, CURLOPT_URL, URL.c_str() );
			curl_easy_setopt( handle, CURLOPT_POSTFIELDS, stringjson.c_str() );
			curl_easy_setopt( handle, CURLOPT_USERAGENT, dat->userAgent.c_str() );
			curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header );
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &json );
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat );
			
			#ifdef DEBUG || _DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			result = curl_easy_perform(handle);
			
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &state );
			s.code = state;
			
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if( result != CURLE_OK )
			{
				set_curl_strerror(s,result); return s;
			} else {
				#ifdef OUTJSON
				std::ofstream out("delete_flair.json");
				out << json;
				#endif
				
				nlohmann::json j = nlohmann::json::parse(json);
				try {
					std::string message = j.at("message");
					int error = j.at("error");
					
					api_error(s,error,message);
					
					return s;
				} catch( nlohmann::json::out_of_range& e )
				{
					#ifdef DEBUG || _DEBUG
					std::cerr << e.what() << std::endl;
					#endif
					
					unknown_error(s); return s;
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
