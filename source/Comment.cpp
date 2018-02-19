#include "subreddit/comments/Comment.hpp"
#include <iostream>

void Comment::convert_json_to_comment(Status& s, std::string json)
{
	// Parse the json into jcomm
	nlohmann::json jcomm = nlohmann::json::parse(json);
	
	nlohmann::json jkind;
	try{
		jkind = jcomm.at("kind");
		std::string kind = jkind.get<std::string>();
		
		if( kind == "t1" ) 
			this->kind = Comment;
		if( kind == "t3" ) 
			this->kind = Link;
		if( kind == "t4" ) 
			this->kind = Message;
	} catch( nlohmann::json::out_of_range& e ) {
		
		#ifdef DEBUG
		std::cerr << e.what() << std::endl;
		#endif
		
		json_error(s,"Failed to get kind data from child");
	}
	
	nlohmann::json data;
	try {
		data = jcomm.at("data");
		
		nlohmann::json approved_at_utc = data.at("approved_at_utc");
		if( !approved_at_utc.is_null() && approved_at_utc.is_number() )
		{
			// If the value exist then assign it to this and assign approved true
			// because since approved_at_utc already exist it implicitly says that
			// it is approved.
			this->approved_at_utc = approved_at_utc.get<long>(); 
			this->approved = true;
		} else {
			this->approved_at_utc = NULL;
		}
		
		nlohmann::json approved_by = data.at("approved_by");
		if( !approved_by.is_null() && approved_by.is_string() ) {
			this->approved_by = approved_by.get<std::string>();
		} else {
			this->approved = "";
		}
		
		this->author = data.at("author");
		
		nlohmann::json author_flair_css_class = data.at("author_flair_css_class");
		if( !author_flair_css_class.is_null() && author_flair_css_class.is_string() ) {
			this->author_flair_css_class = author_flair_css_class.get<std::string>();
		} else {
			this->author_flair_css_class = "";
		}
		
		this->author_flair_text = get_value<std::string>(data.at("author_flair_text"));
		
		
	} catch( nlohmann::json::out_of_range& e ) {
		
		#ifdef DEBUG
		std::cerr << e.what() << std::endl;
		#endif
		
		json_error(s,"Failed to get \"data\" tag from child");
	}

}
