#ifndef VUNSUR_OAUTH
#define VUNSUR_OAUTH

#include "vunsur_basic.hpp"
#inclue "curl/curl.h"
#include "nlohmann/json.hpp"

class VOAUTH
{
	public:
		
		VOAUTH(std::string client_id, std::string secret, std::string username, std::string password, std::string user_agent);
		
		std::vector<std::string> vPerms;
		std::vector<Permissions> Perms;
		State script_authorize();
		
		struct PostAccessData pad;
		struct AccessData ad;
};


#endif
