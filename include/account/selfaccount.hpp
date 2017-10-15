#ifndef SELFACCOUNT_HPP
#define SELFACCOUNT_HPP

#include <curl/curl.h>
#include "json.hpp"

#include "include/authdata.hpp"
#include "include/Exceptions.hpp"
#include "include/condition.hpp"
#include "include/Info.hpp"
#include "include/Error.hpp"

#include "include/items/UserAccount.hpp"
#include "include/items/BasicUser.hpp"
#include "include/items/SubredditKarma.hpp"
#include "include/items/Trophy.hpp"
#include "include/items/UserPrefs.hpp"


#include <vector>
#include <fstream>
#include <cstring>
#include <string>


Status get_self(AccessData* dat, UserAccount* person);
Status get_blocked_users(AccessData* dat); // Does not work for some reason
Status get_friends( AccessData* dat, std::vector< BasicUser* > *f );
Status get_karma( AccessData* dat, std::vector<SubredditKarma*> *sbv );
Status get_trophies( AccessData* dat, std::vector< Trophy *> *vt );
Status get_prefs( AccessData* dat, UserPrefs* up );
Status get_blocked_prefs( AccessData* dat, std::vector< BasicUser* > *buv );
Status get_trusted( AccessData* dat, std::vector< BasicUser* > *tuv );
// get_messagingprefs does not work because it stops working when a trusted user exists
// and it works just fine when a trusted user does not exist? I think this may have something 
// to do with the api itself or I may be just missing something
Status get_messagingprefs( AccessData* dat ); 
#endif
