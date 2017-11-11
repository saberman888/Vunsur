#include "include/base/Types.hpp"


SortType determineSortType(std::string obj)
{
	SortType t;
	if( obj == "Confidence") {
		t = Confidence;
	} else if( obj == "Old") {
		t = Old;
	}
	
	if( obj == "Top" ) {
		t = Top;
	} else if ( obj == "qa" ){
		t = QA;
	}
	
	if( obj == "Controversial" ) {
		t = Controversial;
	} else if ( obj == "New" ) {
		t = New;
	} else {
		t = None;
	}
	return t;
}
