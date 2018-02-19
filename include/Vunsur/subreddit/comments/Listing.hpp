#ifndef LISTING_HPP
#define LISTING_HPP

#include <string>
#include <vector>

#include "base/Types.hpp"

template<class T>
struct Listing {
	std::string before;
	std::string after;
	//std::string modhash;
	std::vector< T > children;
	int size() { return children.size(); }
	//void next();
	//void previous();
};

#endif
