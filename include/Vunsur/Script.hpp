#ifndef VUNSUR_SCRIPT_HPP
#define VUNSUR_SCRIPT_HPP

#include "vunsur_basic.hpp"
#include "curl/curl.h"
#include "nlohmann/json.hpp"
#include <iosfwd>
#include <iomanip>

namespace Vunsur {

	class Script
	{
		public:
			Script(std::string client_id, std::string secret, std::string username, std::string password, std::string user_agent);
			State AuthorizeWithReddit();
		private:
				std::vector<Permission> perms;
				AccessData ad;
				PostAccessData pad;
				friend Script& operator<<(Script& s, Permission p);
	};
	
	Script& operator<<(Script& s, Permission p);
}


#endif
