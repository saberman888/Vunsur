#ifndef OAUTH_HPP
#define OAUTH_HPP


#include "curl/curl.h"
#include "condition.hpp"
#include "authdata.hpp"

#include <vector>
#include <string>
#include <ctime>
#include <iosfwd>

#define println(x) std::cout << x << std::endl;

typedef enum e_permissions
{
	all = 0,
	account,
	creddits,
	edit,
	flair,
	history,
	identity,
	livemanage,
	modconfig,
	modcontributors,
	modflair,
	modlog,
	modmail,
	modothers,
	modposts,
	modself,
	modtraffic,
	modwiki,
	mysubreddits,
	privatemessages,
	read,
	report,
	save,
	structuredstyles,
	submit,
	subscribe,
	vote,
	wikiedit,
	wikiread
}Permission;

//std::vector< std::string > permission_string_list;
class OAUTH
{
	public:
		std::vector<Permission> permissions;
		OAUTH();
		~OAUTH(){}
		
		std::vector<std::string> permission_string_list;
		virtual Status authenticate() { Status s; s.code = NULL; s.cstat = ERROR_NONE; s.message = ""; return s;}

		std::string generate_usrpwd();
		std::string bind_params();
		std::string generate_permissions();
		
		std::string generate_all_permissions();
		
		std::string client_id;
		std::string secret;
		std::string username;
		std::string password;
		
		std::string about_url;
		std::string redirect_uri;
		
		std::string response_type;
		std::string state;
		std::string duration;
		std::string user_agent;

};


#endif
