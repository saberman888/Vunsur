#include "oauth.hpp"
#include <iostream>

OAUTH::OAUTH()
{
	this->permission_string_list = {
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

}



std::string OAUTH::generate_permissions()
{
	int psize = this->permissions.size();
	if( psize == 0 )
	{
		return this->generate_all_permissions();
	} else {
		std::string returnString = "";
		for( int i = 0; i < this->permissions.size(); i++ )
		{
			Permission p = this->permissions[i];
			int pIndex = p;
			std::string pString = this->permission_string_list[pIndex];
			
			returnString += pString;
			
			if( i != psize )
				returnString += "%20";
		}
		return returnString;
	}
}

std::string OAUTH::generate_all_permissions()
{
	std::string bscope = "scope=";
	for( int i = 0; i < this->permission_string_list.size(); i++ )
	{
		std::string elem = this->permission_string_list[i];
		bscope += elem;
		if( i != this->permission_string_list.size() )
			bscope += "%20";
	}
	return bscope;
}

std::string OAUTH::bind_params()
{
	std::string params = ""; // Our return string
	// First generate the permissions
	std::string perms = this->generate_permissions();
	// if there are permissions then add an '&'
	if(perms.empty() == false)
		perms += "&";
		
	params += perms;
	// Add username and password
	params += "grant_type=password&username=";
	params += username;
	params += "&password=";
	params += password;
	return params;
}


std::string OAUTH::generate_usrpwd() {
	return std::string(this->client_id + ":" + this->secret);
}
