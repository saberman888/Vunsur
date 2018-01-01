#ifndef SELFACCOUNT_HPP
#define SELFACCOUNT_HPP

#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

#include "authdata.hpp"
#include "Exceptions.hpp"
#include "condition.hpp"
#include "Info.hpp"
#include "Error.hpp"

#include "UserAccount.hpp"
#include "BasicUser.hpp"
#include "Trophy.hpp"
#include "UserPrefs.hpp"
#include "Holdout.hpp"

#include "subreddit/sub/SubredditKarma.hpp"

#define str_tok(X) #X
#define print(x) std::cout << x << std::endl;

Status get_self(AccessData* dat, UserAccount* person);
Status get_blocked_users(AccessData* dat); // Does not work for some reason
Status get_friends( AccessData* dat, std::vector< BasicUser* > *f );
Status get_karma( AccessData* dat, std::vector<SubredditKarma*> *sbv );
Status get_trophies( AccessData* dat, std::vector< Trophy *> *vt );
Status get_prefs( AccessData* dat, UserPrefs* up );
Status patch_prefs( AccessData* dat, UserPrefs* up ); // patch_prefs is not yet done
Status get_blocked_prefs( AccessData* dat, std::vector< BasicUser* > *buv );
Status get_trusted( AccessData* dat, std::vector< BasicUser* > *tuv );
Status get_about_me( AccessData* dat );
// get_messagingprefs does not work because it stops working when a trusted user exists
// and it works just fine when a trusted user does not exist? I think this may have something 
// to do with the api itself or I may be just missing something
Status get_messagingprefs( AccessData* dat );
#endif
