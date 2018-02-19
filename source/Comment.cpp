#include "subreddit/comments/Comment.hpp"

Comment* convert_json_to_comment(Status& s, std::string json)
{
	// Parse the json into jcomm
	nlohmann::json jcomm = nlohmann::json::parse(json);
	Comment* comm = new(std::nothrow) Comment; // Allocate a new comment so we can store the json data in here
	if(!comm) // If comm has not allocated correctly
	{
		bad_alloc_error(s);
		comm = nullptr;
		return comm;
	} else {
		
		std::string kind;
		try{
			kind = jcomm.at("kind");
			
			if( kind == "t1" ) comm->kind = Comment;
			if( kind == "t3" ) comm->kind = Link;
			if( kind == "t4" ) comm->kind = Message;
		} catch( nlohmann::json::out_of_range& e ) {
			
			#ifdef DEBUG
			std::cerr << e.what() << std::endl;
			#endif
			
			json_error(s,"Failed to get kind data from child");
			delete comm; comm = nullptr;
			return comm;
		}
		
		nlohmann::json data;
		try {
			data = jcomm.at("data");
			
			nlohmann::json approved_at_utc = data.at("approved_at_utc");
			if( !approved_at_utc.is_null() && approved_at_utc.is_number() )
			{
				// If the value exist then assign it to comm and assign approved true
				// because since approved_at_utc already exist it implicitly says that
				// it is approved.
				comm->approved_at_utc = approved_at_utc.dump(); comm->approved = true;
			} else {
				comm->approved_at_utc = NULL;
			}
			
			nlohmann::json approved_by = data.at("approved_by");
			if( !approved_by.is_null() && approved_by.is_string() ) {
				comm->approved_by = approved_by.dump();
			} else {
				comm->approved = "";
			}
			
			comm->author = data.at("author");
			
			nlohmann::json author_flair_css_class = data.at("author_flair_css_class");
			if( !author_flair_css_class.is_null() && author_flair_css_class.is_string() ) {
				comm->author_flair_css_class = author_flair_css_class.dump();
			} else {
				comm->author_flair_css_class = "";
			}
			
			comm->author_flair_text = get_value<std::string>(data.at("author_flair_text"));
			
			
			return comm;
			
		} catch( nlohmann::json::out_of_range& e ) {
			
			#ifdef DEBUG
			std::cerr << e.what() << std::endl;
			#endif
			
			json_error(s,"Failed to get \"data\" tag from child");
			delete comm; comm = nullptr;
			return comm;
		}
	}
}
