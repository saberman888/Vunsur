#include "vunsur\vunsur_basic.hpp"
#include <iostream>

namespace Vunsur {
	std::string generate_parameters(const AccessData & ad, const std::vector<Permission>& ps)
	{
		std::vector<std::string> permission_string_list = {
			"account",
			"creddits",
			"edit",
			"flair",
			"history",
			"identity",
			"livemanage",
			"modconfig",
			"modcontributors",
			"modflair",
			"modlog",
			"modmail",
			"modothers",
			"modposts",
			"modself",
			"modtraffic",
			"modwiki",
			"mysubreddits",
			"privatemessages",
			"read",
			"report",
			"save",
			"structuredstyles",
			"submit",
			"subscribe",
			"vote",
			"wikiedit",
			"wikiread"
		};

		// First of all generate the permissions first
		std::string permissions = ""; // where I will hold the permissions
		int psize = (int)ps.size();
		if (psize != 0)
		{
			std::string temp;
			for (auto& elem : ps)
			{
				temp += permission_string_list[(int)elem];
				temp += "%20";
			}
		}
		else {
			// If there are no permissions that means (by default) all permissions will be added
			for (std::string s : permission_string_list)
			{
				permissions.append(s);
				permissions.append("%20");
			}
		}

		// Now to bind the permission to the rest of the params
		std::string params = "&";
		params += permissions;
		params += "grant_type=password&username=";
		params += ad.username;
		params += "&password";
		params += ad.password;

		// done and return the final result
		return params;
	}
	std::ostream & operator<<(std::ostream & out, const State s)
	{
		out << "State: " << s.cstat << ", Code:" << s.code; return out;
	}
	void set_state(State& s, EState es, int code, std::string message)
	{
		s.cstat = es;
		s.code = code;
		s.message = message;
	}
	bool State::all_good()
	{
		if (this->cstat == ERROR_NONE && this->code == 200)
			return true;
		return false;
	}


	size_t writedat(char* buffer, size_t size, size_t nmemb, std::string& src)
	{
		for (size_t i = 0; i < size * nmemb; i++)
		{
			src.push_back(buffer[i]);
		}
		return size * nmemb;
	}

}
