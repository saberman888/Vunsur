#include "include/Script.hpp"
#include <iostream>

// The constructor for ScriptAccess
// The reason why the parameter variables are
// const char* types is because they can be denied easier. In a char* and const char* you can put NULL or
// nullptr while with a std::string you cannot
ScriptAccess::ScriptAccess( const char* client_id, const char* secret, const char* username, const char* password, const char* userAgent )
{

	// I put the conditions in the variable keyvarif because it was easier to type it out and whatnot
	// This checks if the variables client_id and secret are there, if not then NoMainKeys() will be thrown
	bool keyverif = ( ( client_id == NULL || client_id == nullptr ) && ( secret == NULL || secret == nullptr ) );
	if(keyverif == true)
	{
		// If client_id and secret are NULL or nullptr then throw this exception
		throw NoMainKeys();
	}
	// If client_id and secret are there then assign them to the class' equivalent
	this->client_id = client_id;
	this->secret = secret;
	// Acd is the structure that holds the access tokenm, it's type, scope and expire time
	// It is nullptr because we don't need to do much with it right now
	this->acd = nullptr;
	// Next pass_null checks if the username and password are tere
	bool pass_null = ( (username == NULL || username == nullptr) && (password == NULL || password == nullptr) );
	if( pass_null == true )
	{
		// If the username and password are not there then set loginAccess to false
		// This bool exists so we can see if the user is logged in or not
		this->loginAccess = false;
	} else {
		// If the username and password are there then set 
		// loginAccess to true and assign username and password
		// to the class' equivalent and store then there
		this->loginAccess = true;
		this->username = username;
		this->password = password;
	}
	// Like client_id and secret, the user Agent is a requirment
	// If it is there then assign it to the class' equivalent
	// If it is not there then throw the NoUserAgent exception
	if( userAgent == NULL || userAgent == nullptr )
	{
		// Throw this exception if the userAgent isn't there
		throw NoUserAgent();
	}
	this->userAgent = userAgent;
	
	// Done
	
}

// The destructor
ScriptAccess::~ScriptAccess(){
	// If acd exists then delete it.
	// If not then don't and be done
	if(this->acd != nullptr)
		delete this->acd;
}

// AuthorizeWithReddit wrapps around the authenticate function with some extra stuff
Status ScriptAccess::AuthorizeWithReddit()
{
	// Status s variable is the variable which holds information on
	// the success of this function and failure
	Status s;
	// Allocate a new AccessData instance 
	// and pass it to authenticate function
	this->acd = new AccessData; 
	// Also assign the userAgent to acd
	this->acd->userAgent = this->userAgent;
	// authenticate returns information about the success and/or failure
	// of the function and stores it in s. If it has succeeded then 
	// it should return a code 200, and if not then delete acd
	s = authenticate(this, acd);
	if( s.code != 200)
		delete this->acd;
	// If the message is an invalid grant then the user is 
	// not logged in or failed to do so, and set loginAccess to false
	if( s.message == "invalid_grant" )
		this->loginAccess = false;
	// Whether or not it has succeeded return s
	return s;
}
// Me wraps around the get_self function and it returns data of the user currently logged in
Status ScriptAccess::getMe()
{
	Status me;
	if( this->loginAccess == true)
	{
		// If it this person is logged in then proceed to attempt to get user data
		// If it is successful then return Succ/Fail data into me and return it
		me = get_self(this->acd, this->acc);
		
		// Before returning lets get the mod hash
		this->acd->modhash = this->acc->modhash;
		return me;
	} else {
		// If the user is not logged in then set code to NULL
		// set cstat to ERROR_NOT_LOGGED_IN and the message to
		// a error messaged about not being logged in
		me.code = NULL;
		me.cstat = ERROR_NOT_LOGGED_IN;
		me.message = "Error: Not logged in";
		return me;
	}
}

// BlockedUsers wraps around the function get_blocked_users from account.hpp and acount.cpp
// It is not quite finished yet, and it acts the same way as the other functions: Me(), Friends() and etc
Status ScriptAccess::getBlockedUsers(){ // does not work
	if( this->loginAccess == true){
	
		return get_blocked_users( this->acd );
	}
	else {
		Status s;
		s.code = 0;
		s.cstat = ERROR_NOT_LOGGED_IN;
		s.message = "Error: Not logged in";
		
		return s;
	}
}
// This functions, Friends, like many others wraps around another function. Friends wraps around get_friends
// from account.hpp/.cpp. It take a std::vector< Friend * > * and requests a list of friends from Reddit
// and parses them into the vector, and in the end it returns a Status type
Status ScriptAccess::getFriends(std::vector< BasicUser* > * f )
{
	if( this->loginAccess == true ) {
		return get_friends( this->acd,  f);
	} else {
		Status s;
		s.code = NULL;
		s.cstat = ERROR_NOT_LOGGED_IN;
		s.message = "Error: Not logged in";
		return s;
	}
}

Status ScriptAccess::getUserAbout( std::string username, UserAccount* ua )
{
	return aboutUser(this->acd, username, ua);
}

// SubredditKarma wraps around the function get_karma from account.hpp/cpp and it returns a list of karma by subreddit
Status ScriptAccess::getSubredditKarma( std::vector<SubredditKarma*> *sbv )
{
	if( this->loginAccess == true )
	{
		return get_karma( this->acd, sbv );
	} else {
		Status s;
		s.code = NULL;
		s.cstat = ERROR_NOT_LOGGED_IN;
		s.message = "Error: Not logged in";
		return s;
	}
	
}

// Wraps arround the get_trophies function
Status ScriptAccess::getTrophies( std::vector< Trophy* > *trophies ) {
	if( this->isLoggedIn() )
	{
		return get_trophies(this->acd, trophies);
	} else {
		Status s;
		s.code = NULL;
		s.cstat = ERROR_NOT_LOGGED_IN;
		s.message = "Error: Not logged in";
		return s;
	}
}

// Get getPrefs wrapps around the get_prefs function 
Status ScriptAccess::getPrefs(UserPrefs* up) {
	if( this->isLoggedIn() ) {
		return get_prefs(this->acd, up);
	} else {
		Status s;
		s.code = NULL;
		s.cstat = ERROR_NOT_LOGGED_IN;
		s.message = "Error: Not logged in";
		return s;
	}
}

Status ScriptAccess::patchPrefs( UserPrefs* up ) {
	if( this->isLoggedIn() ) {
		return patch_prefs(this->acd, up);
	} else {
		Status s;
		not_logged_in(s); return s;
	}
}

Status ScriptAccess::getBlockedPrefs(std::vector< BasicUser*> *buv) {
	if( this->isLoggedIn() ) {
		return get_blocked_prefs(this->acd, buv);
	} else {
		Status s;
		not_logged_in(s);
		return s;
	}
}

Status ScriptAccess::getTrustedPrefs( std::vector< BasicUser* > *tuv ) {
	Status s;
	if ( this->isLoggedIn() ) {
		return get_trusted(this->acd, tuv);
	} else {
		not_logged_in(s);
		return s;
	}
}

// Since the get_messagingprefs() does not work it will throw a FunctionUnavailable() exception
Status ScriptAccess::getMessagingPrefs() {
	if( this->isLoggedIn() ) {
		//return get_messagingprefs(this->acd);
		throw FunctionUnavailable();
	} else {
		Status s;
		s.code = NULL;
		s.cstat = ERROR_NOT_LOGGED_IN;
		s.message = "Error: Not logged in";
		return s;
	}
}

Status ScriptAccess::giveGold( std::string username ) {
	if( this->isLoggedIn() ) {
		return give_gold(this->acd, username);
	} else {
		Status s;
		s.code = NULL;
		s.cstat = ERROR_NOT_LOGGED_IN;
		s.message = "Error: Not logged in";
		return s;
	}
}

// Authenticate function connects to reddit to get a access token so the user can
// have the priviledge of using Reddit's API. It takes a ScriptAccess* variable and an 
// AccessData and with it POST requests an access token
Status authenticate( ScriptAccess* src, AccessData* acs )
{
	
	// Declare result, handle and returndata
	CURLcode result;
	CURL* handle;
	// Initialize handle with curl_easy_init
	handle = curl_easy_init();
	// This is where I will be storing the json data
	// collected from the POST request
	std::string returndata;
	// Status code for the operation
	int status_code;
	// Needed status variable
	Status s;
	// If handle initializes successfully then proceed
	if(handle)
	{
		// Initialize curl_global with CURL_GLOBAL_SSL and store the result in CURLcode globalres
		CURLcode globalres = curl_global_init( CURL_GLOBAL_SSL );
		// Then make sure curl_global initialized fully with no fails
		// if it has not failed then proceed
		if( globalres == CURLE_OK )
		{
			// Set the URL address and enable POST requests
			curl_easy_setopt( handle, CURLOPT_URL, "https://www.reddit.com/api/v1/access_token" );
			curl_easy_setopt( handle, CURLOPT_POST, 1L );
			
			// These params will hold the username and password
			std::string params = "grant_type=password&username=";
			// and if the loginAccess is true then append the user's
			// username and password to the params
			if(src->loginAccess == true)
			{
				params += src->username;
				params += "&password=" + src->password;
			}
			// then set the params into the POST request
			curl_easy_setopt( handle, CURLOPT_POSTFIELDS, params.c_str() );
			// Set the client and secret with userpwd
			std::string userpwd = src->client_id + ":" + src->secret;
			curl_easy_setopt( handle, CURLOPT_USERPWD, userpwd.c_str() );
			// Set the userAgent
			curl_easy_setopt( handle, CURLOPT_USERAGENT, src->userAgent.c_str() );
			// Set SSL_VERIFYPEER to 0L
			curl_easy_setopt( handle, CURLOPT_SSL_VERIFYPEER, 0L );
			
			// If DEBUG is defined set CURLOPT_VERBOSE to 1L
			#ifdef DEBUG
			curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
			#endif
			
			// write functions
			curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, &writedat);
			// Assign returndata to be the string holding the json data
			curl_easy_setopt( handle, CURLOPT_WRITEDATA, &returndata);
			
			// And finally the operation performs!
			result = curl_easy_perform( handle );
			// Once done clean up everything
			curl_easy_cleanup( handle );
			curl_global_cleanup();
			
			// Get the status code of the operation and assign it to status_code
			curl_easy_getinfo( handle, CURLINFO_RESPONSE_CODE, &status_code);
			
			if( result != CURLE_OK )
			{
				// If handle's operation failed then print out the curl error message
				// if DEBUG is defined and set the status accordingly
				#ifdef DEBUG
				std::cerr << "curl_easy_strerror(): " << curl_easy_strerror(result) << std::endl;
				#endif
				s.code = status_code ;
				s.cstat = ERROR_CURL_STRERROR;
				s.message = curl_easy_strerror( result );
				
				return s;
				
			} else {
				
				// If everything succeeds then proceed to extract the json
				
				// If DEBUG is available then print out the json data
				#ifdef DEBUG
				std::cout << returndata << std::endl;
				#endif
				
				// Parse the json
				auto j = nlohmann::json::parse(returndata);
				// declare the necessary variables
				std::string acctoken;
				std::string scope;
				std::string type;
				int expires_in;
				// and then attempt to extract the needed data
				try{
					acctoken = j.at("access_token");
					scope = j.at("scope");
					type = j.at("token_type");
					expires_in = j.at("expires_in");
						
				} catch( nlohmann::json::out_of_range& e ) {
					try {
						// If extracting the values fails then try to extract error values
						std::string error_msg = j.at("message");
						int code = j.at("error");
						// print error message if debug is defined
						#ifdef DEBUG
						std::cerr << "Error: " << error_msg << ", code: " << code << std::endl;
						#endif
						// set status and return
						s.code = status_code;
						s.cstat = ERROR_NONE;
						s.message = error_msg;
					
						return s; // return 
					} catch( nlohmann::json::out_of_range& e ) {
						try {
							// If obtaining the error fails then maybe
							// the error is an unsupported_grant_type
							std::string error = j.at("error");
							s.code = status_code;
							s.cstat = ERROR_NONE;
							s.message = error;
							if( error == "unsupported_grant_type" )
							{
								#ifdef DEBUG
								std::cerr << "Error: Unsupported grant type " << std::endl;
								#endif
								
								return s;
							} else if( error == "invalid_grant" ) {
								
								// If it isn't unsupported grant_type then it is probably a invalid grant
								#ifdef DEBUG
								std::cerr << "Error: Invalid grant" << std::endl;
								#endif
								
								return s;
							}
							return s;
						} catch( nlohmann::json::out_of_range& e )
						{
							// If everything fails then return an Unknown error
							unknown_error(s);
							
							return s;
						}
					}
				}
				
				
				// Since we got all the values we need assign them
				// to the proper places in the acs struct
				acs->token = acctoken;
				acs->token_type = type;
				acs->scope = scope;
				
				// Convert the expired time to time now
				time_t t = time(0);
				struct tm * now = localtime(&t);
				// Since most expire times are 3600, which is 1 hour
				// add 1 to the hour variable to the now struct.
				// There might be more times, but as for now I don't know
				if(expires_in == 3600)
					now->tm_hour += 1;
				
				acs->expire = now;
				// set status
				s.code = status_code;
				s.cstat = ERROR_NONE;
				s.message = "";
				// and reeeeeeeeeeeeturn!
				return s;
			}
		} else {
			// If curl global fails then it will end up here, and if DEBUG is defined
			// then it will print out this error message
			#ifdef DEBUG
			std::cerr << "Error: Failed to initialize CURL GLOBAL " << std::endl;
			#endif
			// Since failure has occured clean up the handle and configure the status accordingly
			curl_easy_cleanup(handle);
			s.code = NULL;
			s.cstat = ERROR_CURL_GLOBAL_FAILED_INIT;
			s.message = "Error: Failed to initialize CURL GLOBAL";
			// and finally return it
			return s;
		}
		
	} else {
		// If handle failed to initialize then print out
		// a error message only if DEBUG preprocessor directive is defined
		#ifdef DEBUG
		std::cerr << "Error: Failed to initialize CURL * handle " << std::endl;
		#endif
		// Configure the status variable. Since there isn't a server error
		// then set s.code to NULL, then set s.cstat to the proper library
		// error along with the message.
		s.code = NULL;
		// Since in this case, handle has failed, then set s.cstat to ERROR_CURL_HANDLE_FAILED_INIT;
		s.cstat = ERROR_CURL_HANDLE_FAILED_INIT;
		s.message = "Error: Failed to initialize CURL * handle ";
		// And then finally return the shebang
		return s;
	}
	
}
