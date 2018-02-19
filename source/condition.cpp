#include "condition.hpp"
#include <iostream>

void Status::print_state() 
{ 
	std::cerr << "Code: " << this->code << "; " << this->message << "; EStatus: " << this->cstat << std::endl; 
}

bool Status::all_good()
{
	return ( this->code == 200 && this->cstat == ERROR_NONE );
}

