#ifndef VUNSUR_BASIC_H
#define VUNSUR_BASIC_H

#include <string>
#include <vector>
#include <ctime>
#include <iosfwd>

namespace Vunsur{
	typedef enum e_permissions
	{
		account = 0,
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
	
	std::string generate_parameters(const struct AccessData &ad, const std::vector<Permission>& ps);
	// Structures used to authenticate and get from Reddit
	struct PostAccessData
	{
		std::string token;
		std::string token_type;
		std::string scope;
		struct tm * expire;
		std::string userAgent;
	};

	// the entry level structure used for 
	struct AccessData
	{
		std::string client_id;
		std::string secret;
		std::string username;
		std::string password;
		std::string useragent;
	};
	
	// State, where we will have our data for State
	// EState or _error_State is an enum that defines
// errors needed for the library
	typedef enum _error_State
	{
		ERROR_NONE, // 0
		ERROR_CURL_HANDLE_FAILED_INIT, // 1
		ERROR_CURL_GLOBAL_FAILED_INIT, // 2
		ERROR_CURL_STRERROR, // 3
		ERROR_NOT_LOGGED_IN, // 4
		ERROR_UNSUPPORTED_GRANT_TYPE, // 5
		ERROR_UNKNOWN_ERROR, // 6
		ERROR_JSONERROR, // 7
		ERROR_BAD_ALLOCATION // 8
	}EState;

	class State
	{
	public:
		std::string message;
		EState cstat;
		int code;
		bool all_good();
		friend std::ostream& operator<<(std::ostream& out, const State s);
	};

	std::ostream& operator<< (std::ostream& out, const State s);

	// functions for setting state
	void set_state(State& s, EState es, int code, std::string message);
	size_t writedat(char* buffer, size_t size, size_t nmemb, std::string& src);
}

#endif
