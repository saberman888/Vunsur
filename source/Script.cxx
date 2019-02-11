#include "vunsur\Script.hpp"
#include <fstream>
namespace Vunsur {

	Script::Script(std::string client_id, std::string secret, std::string username, std::string password, std::string user_agent)
	{
		ad.client_id = client_id;
		ad.secret = secret;
		ad.password = password;
		ad.useragent = user_agent;
	}
	
	State Script::AuthorizeWithReddit()
	{
		State result;
		CURLcode cresult;
		CURL *handle;
		std::string json;
		int hc;
		handle = curl_easy_init();
		
		if(!handle)
		{
			
			set_state(result, ERROR_CURL_HANDLE_FAILED_INIT, 0, "Failed to initialize CURL");
		} else {
			curl_global_init(CURL_GLOBAL_SSL);
			curl_easy_setopt(handle, CURLOPT_URL, "https://oauth.reddit.com/access_token");
			curl_easy_setopt(handle, CURLOPT_POST, 1L);
			
			std::string params = generate_parameters(ad, perms);
			
			curl_easy_setopt(handle, CURLOPT_POSTFIELDS, params.c_str());
			std::string userpwd = ad.username + ":" + ad.password;
			curl_easy_setopt(handle, CURLOPT_USERPWD, userpwd.c_str());
			curl_easy_setopt(handle, CURLOPT_USERAGENT, ad.useragent.c_str());
			
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, &json);
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &writedat);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
			
			#ifdef DEBUG
			curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
			#endif
			
			cresult = curl_easy_perform(handle);
			
			hc = curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, hc);
			curl_easy_cleanup(handle);
			curl_global_cleanup();
			
			if(cresult != CURLE_OK)
			{
				set_state(result, ERROR_CURL_STRERROR, hc, curl_easy_strerror(cresult));
			} else {
				std::ofstream out("access_token.json");
				out << std::setw(4) << json << std::endl;
			}
		}
		return result;
	}
	
	Script& operator<<(Script& s, Permission p)
	{
		s.perms.push_back(p);
		return s;
	}
}
