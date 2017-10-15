#ifndef UserAccount_HPP
#define UserAccount_HPP

#include "include/base/Created.hpp"
#include <string>

// This structure that stores user information for any account
typedef struct user_acc : public Created {

	
	// The karma of the account
	int CommentKarma;
	int LinkKarma;
	
	int gold_creddits;
	
	// User's name and id
	std::string name;
	std::string user_id; // The user id
	
	// Creation dates
	//long created;
	//long created_utc; // the utc version
	
	// whether said user is over 18
	bool over_18;
	bool is_suspended;
	bool is_gold; // if user has gold
	bool in_beta;
	bool is_employee;
	bool is_sponsor;
	bool is_friend;
	// Moderation related things
	bool is_mod;
	
	// Mail related things
	int inbox_count;
	char* modhash;
	bool has_mail;
	bool has_mod_mail;
	bool has_verified_email;
}UserAccount;

#endif