#ifndef OTHER_FUNCTIONS_HPP
#define OTHER_FUNCTIONS_HPP

#include <string>
#include <iosfwd>
#include "curl/curl.h"

#include "condition.hpp"
#include "Error.hpp"
#include "authdata.hpp"
#include "Info.hpp"

Status scopes( AccessData* dat ); 

#endif
