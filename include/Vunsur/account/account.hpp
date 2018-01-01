#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

#include "authdata.hpp"
#include "sceExceptions.hpp"
#include "condition.hpp"

typedef struct _self
{

	
	// The karma of the account
	int CommentKarma;
	int LinkKarma;
	
	int gold_creddits;
	
	// User's name and id
	std::string name;
	std::string user_id; // The user id
	
	float created;
	float created_utc;
	
	// whether said user is over 18
	bool over_18;
	bool is_suspended;
	bool is_gold; // if user has gold
	bool in_beta;
	bool is_employee;
	bool is_sponsor;
	// Moderation related things
	bool is_mod;
	
	// Mail related things
	int inbox_count;
	char* modhash;
	bool has_mail;
	bool has_mod_mail;
	bool has_verified_email;
}Self;

typedef struct usr_acc : public Self
{
	// Boolean whether the user is friends with this account
	// It only applies to accounts other than Self or the user logged in
	bool is_friend;
}UserAccount;


typedef struct _friend
{
	float date;
	std::string id;
	std::string name;
}Friend;

Status get_self(AccessData* dat, std::string userAgent, Self * person);
size_t writedat(char* buffer, size_t size, size_t nmemb, std::string& src);
void get_blocked_users(AccessData* dat, std::string userAgent);
std::vector< Friend* > get_friends(AccessData* dat, std::string userAgent);


#endif
