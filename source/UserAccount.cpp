#include "include/items/UserAccount.hpp"

UserAccount::UserAccount() {
	
}

UserAccount::~UserAccount() {
	delete default_srs_holdout;
	delete geopopular_gb_holdout;
	delete geopopular_ie_holdout;
	delete geopopular_in_holdout;
	delete geopopular_tw_holdout;
	delete mweb_xpromo_ad_feed_ios;
	delete search_public_traffic;
	delete subreddit;
}
