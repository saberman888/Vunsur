#ifndef USER_HPP
#define USER_HPP

#include "include/account/selfaccount.hpp"
#include "include/condition.hpp"
#include "include/Info.hpp"
#include "include/Error.hpp"
#include <string>

// aboutUser get's the user's about data
Status aboutUser( AccessData* acd, std::string username, UserAccount* ua );
#endif
