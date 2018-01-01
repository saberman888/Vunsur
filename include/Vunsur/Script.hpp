#ifndef SCRIPT_HPP
#define SCRIPT_HPP

/* dir includes */
#include "authdata.hpp"
#include "Exceptions.hpp"
#include "Info.hpp"
#include "other.hpp"

/* account includes */
#include "account/selfaccount.hpp"
#include "account/user.hpp"

/* subreddit includes */
#include "subreddit/gold.hpp"
#include "subreddit/sub/flair/Flair.hpp"
#include "subreddit/sub/subreddit.hpp"
#include "subreddit/sub/linkncomms.hpp"

/* basic compiler includes */
#include <string>
#include "curl/curl.h"
#include "json.hpp"
#include <ctime>

// The ScriptAccess class is for Script based Reddit api applications
class ScriptAccess {
	public:

		// The constructor
		ScriptAccess(  const char* client_id, const char* secret, const char* username, const char* password, const char* userAgent  ); 
		ScriptAccess(); // An empty constructor for those not using client_ids, secrets and usernames/passwords
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
		Status gild( std::string fullname ); // gilds a post
		
		// ********* FLAIR FUNCTIONS *********
		Status ClearFlairTemplates( std::string subreddit, FlairType ft);
		Status DeleteFlair( std::string subreddit, std::string flair_name );
		
		//********** SUBREDDIT FUNCTIONS *********
		Status getAboutSubreddit( std::string subreddit, SubredditInfo *sub );
		Status getSubredditSetting( std::string subreddit );
		
		//********** USER FUNCTIONS ***************/
		Status getUserSaved( std::string username ); // Does not work for now
		
		
		/************* LISTING FUNCTIONS **********/
		Status getTrending();
		
		/************ LINKS AND COMMENTS *********/
		Status Comment( std::string parent, std::string text ) { return comment(this->acd, parent, text ); }
		Status deleteComment( std::string fullname );
		Status editComment( std::string id, std::string text );
		
		
		/************ OTHER FUNCTIONS *************/
		Status Scopes() { return scopes(this->acd); }
		
		
		std::string getUsername() { return this->username; }
		std::string getClientId() { return this->client_id; }
		bool isLoggedIn() { return this->loginAccess; }
		UserAccount* Me() { return this->acc; }
		std::string Scope() { return this->acd->scope; }
		struct tm* ExpireTime() { return this->acd->expire; }
		
	private:
		friend Status authenticate( ScriptAccess* src, AccessData* acs );
		
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
		
		// The acd variable holds access_token, token type, scope and expire time
		AccessData* acd;

};

// From Info.cpp, this writes buffer data into src - a string
//size_t writedat(char* buffer, size_t size, size_t nmemb, std::string& src);
// Declaration for the function to get a access token from Reddit
Status authenticate( ScriptAccess* src, AccessData* acs );

#endif
