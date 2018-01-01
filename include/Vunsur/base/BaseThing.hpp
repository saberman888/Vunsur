#ifndef BASE_THING_HPP
#define BASE_THING_HPP

#include <string>
#include "Types.hpp"

typedef struct _base {
	std::string id;
	std::string name;
	VunType kind;
}BaseThing;

#endif
