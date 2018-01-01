#ifndef TROPHY_HPP
#define TROHPY_HPP

#include "base/BaseThing.hpp"

typedef struct _trophy : public BaseThing {
	std::string award_id;
	std::string description;
	std::string icon40;
	std::string icon70;
}Trophy;

#endif
