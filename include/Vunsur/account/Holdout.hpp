#ifndef HOLDOUT_HPP
#define HOLDOUT_HPP

#include <string>

typedef struct _holdout {
	int experiment_id;
	std::string owner;
	std::string variant;
}Holdout;
#endif
