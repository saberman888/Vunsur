#ifndef USER_HPP
#define USER_HPP

#include "account/selfaccount.hpp"
#include "condition.hpp"
#include "Info.hpp"
#include "Error.hpp"
#include <string>


Status get_user_trophies( AccessData* acd, std::string username);
// aboutUser get's the user's about data
Status aboutUser( AccessData* acd, std::string username, UserAccount* ua );
Status get_about_saved( AccessData* dat, std::string username );
#endif
