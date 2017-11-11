#include "include/base/Types.hpp"


SortType determineSortType(std::string obj)
{
	SortType t;
	switch(	obj.c_str() ) {
		case "Confidence": t = Confidence; break;
		case "Old": t = Old; break;
		case "Top": t = Top; break;
		case "qa" : t = QA; break;
		case "Controversial": t = Controversial; break;
		case "New": t = New; break;
		default: t = None; break;
		
			
	}
	return t;
}
