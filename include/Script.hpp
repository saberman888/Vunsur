#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "include/authdata.hpp"
#include "include/Exceptions.hpp"
#include "include/account/selfaccount.hpp"
#include "include/account/user.hpp"
#include "include/gold/gold.hpp"
#include "include/Info.hpp"
#include "include/flair/Flair.hpp"

#include <string>
#include "curl/curl.h"
#include "json.hpp"
#include <ctime>

// The ScriptAccess class is for Script based Reddit api applications
class ScriptAccess {
	public:

		// The constructor
		ScriptAccess(  const char* client_id, const char* secret, const char* username, const char* password, const char* userAgent  ); 
		~ScriptAccess(); // The deconstructor
		// This function authorized with reddit with the "main data"
		// and returns data to access the ret of the API
		// It returns a structure called Status which has
		// data whether or not the POST request for access
		// was successful
		Status AuthorizeWithReddit();
		// this function returns Userdata about the
		// account logged in, it also returns a Status structure
		Status getMe();
		// Blocked users isn't quite finished
		// It returns an array of blocked users
		Status getBlockedUsers(); // Does not work
		// Friends returns an array of friends from the logged in user
		Status getFriends(std::vector< BasicUser *>* f);
		// SubredditKarma function gets the logged in user's karma by subreddit
		Status getSubredditKarma( std::vector< SubredditKarma* >* sbv );
		// Gets the trophies of the user logged in
		Status getTrophies( std::vector< Trophy* > *trophies );
		// Gets the prefs settings for the user's account
		Status getPrefs(UserPrefs *up);
		// Returns a list of blocked users from your blocked prefs
		Status patchPrefs( UserPrefs* up );
		Status getBlockedPrefs(std::vector< BasicUser*> *buv);
		// Gets the trusted preferences
		Status getTrustedPrefs( std::vector< BasicUser* > *tuv );
		// Gets messaging preferences. Getting messaging preferences returns trusted users and bocked users
		// get_messagingprefs does not work because it stops working when a trusted user exists
		// and it works just fine when a trusted user does not exist? I think this may have something 
		// to do with the api itself or I may be just missing something
		Status getMessagingPrefs(); // Unavailable
		// Everything about getting other user's information goes below here 
		// getUserAbout get's user information about a user
		Status getUserAbout( std::string username, UserAccount* ua );
		
		// ********* GOLD FUNCTIONS **********
		// This function gives gold a user
		Status giveGold( std::string username );
		
		// ********* FLAIR FUNCTIONS *********
		Status ClearFlairTemplates( std::string subreddit, FlairType ft);
		
		
		friend Status authenticate( ScriptAccess* src, AccessData* acs );
		
		std::string getUsername() { return this->username; }
		std::string getClientId() { return this->client_id; }
		bool isLoggedIn() { return this->loginAccess; }
		UserAccount* Me() { return this->acc; }
		
	private:
		// Our main data to enter the Reddit API
		std::string client_id;
		std::string secret;
		// If the username and password are not
		// provided then loginAccess will be false
		std::string username;
		std::string password;
		std::string userAgent; // This is absolutely necessary, if not provided then NoUserAgent exception will be thrown
		
		// A UserAccount instance for the logged in user
		UserAccount* acc;
		// This bool indicates whether the class has login access
		// and it will determine your functionality access accross
		// this API
		bool loginAccess;
		// A boolean for modhash access
		bool modhash_access;
		bool ModhashExists() { return this->modhash_access; }
		// The acd variable holds access_token, token type, scope and expire time
		AccessData* acd;

};

// From Info.cpp, this writes buffer data into src - a string
//size_t writedat(char* buffer, size_t size, size_t nmemb, std::string& src);
// Declaration for the function to get a access token from Reddit
Status authenticate( ScriptAccess* src, AccessData* acs );

#endif
