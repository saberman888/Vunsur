#include "include/condition.hpp"
#include <iostream>

void print_status(Status s ) 
{ 
	std::cout << "Code: " << s.code << "; " << s.message << "; EStatus: " << s.cstat << std::endl; 
}
