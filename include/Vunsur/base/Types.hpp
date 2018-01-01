#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

typedef enum VunTypes {
	Comment = 1,
	Account = 2,
	Link = 3 ,
	Message = 4 ,
	Subreddit = 5 ,
	Award = 6
}VunType;

typedef enum SortTypes {
	None,
	Confidence,
	Old,
	Top,
	QA,
	Controversial,
	New
}SortType;

SortType determineSortType(std::string obj);

typedef enum  scopes {
	Submit,
	PrivateMessages
}Scope;


typedef enum Regions {
	GLOBAL,
	US, AR, AU, 
	BG, CA,
	CL, CO, HR, 
	CZ, FI,
	GR, HU, IS,
	_IN, IE,
	JP, MY, MX,
	NZ, PH,
	PL, PT, PR,
	RO, RS,
	SG, SE, TW,
	TH, TR, 
	GB,
	
	US_DE, US_DC, US_WI, US_WV,
	
	US_HI, US_FL, US_WY, US_NH,
	
	US_NJ, US_NM, US_TX, US_LA,
	
	US_NC, US_ND, US_NE, US_TN,
	
	US_NY, US_PA, US_CA, US_NV,
	
	US_VA, US_CO, US_AK, US_AL,
	
	US_AR, US_VT, US_IL, US_GA,
	
	US_IN, US_IA, US_OK, US_AZ,
	
	US_ID, US_CT, US_ME, US_MD,
	
	US_MA, US_OH, US_UT, US_MO,
	
	US_MN, US_MI, US_RI, US_KS,
	
	US_MT, US_MS, US_SC, US_KY,
	
	US_OR, US_SD
}Region;



#endif
