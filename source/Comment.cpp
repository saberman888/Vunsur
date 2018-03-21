#include "subreddit/comments/Comment.hpp"
#include <iostream>

void VunComment::convert_json_to_comment(nlohmann::json& src)
{
	nlohmann::json data = src.at("data");
	
	this->approved_at_utc = get_long_value( data.at("approved_at_utc") );
	this->approved = get_boolean_value( data.at("approved") );
	this->approved_by = get_string_value( data.at("approved_by") );
	this->archived =  get_boolean_value( data.at("archived") );
	this->author = get_string_value( data.at("author") );
	this->author_flair_css_class = get_string_value( data.at("author_flair_css_class") );
	this->author_flair_text = get_string_value( data.at("author_flair_text") );
	this->banned_at_utc = get_long_value( data.at("banned_at_utc") );
	this->banned_by = get_string_value( data.at("banned_by") );
	this->body = get_string_value( data.at("body") );
	this->body_html = get_string_value( data.at("body_html") );
	this->can_guild = get_boolean_value( data.at("can_guild") );
	this->can_mod_post = get_boolean_value( data.at("can_mod_post") );
	this->collapsed = get_boolean_value( data.at("collapsed") );
	this->collapsed_reason = get_string_value( data.at("collapsed_reason") );
	this->controversiality = get_integer_value( data.at("controversiality") );
	this->created = get_long_value( data.at("created") );
	this->created_utc = get_long_value( data.at("created_utc"));
	this->depth = get_integer_value( data.at("depth") );
	this->distinguished = get_string_value( data.at("distinguished") );
	this->downs = get_integer_value( data.at("downs") );
	this->edited = get_boolean_value( data.at("edited") );
	this->gilded = get_integer_value( data.at("gilded") );
	this->ignore_reports = get_boolean_value( data.at("ignore_reports") );
	this->is_submitter = get_boolean_value( data.at("is_submitter") );
	this->link_id = get_string_value( data.at("link_id") );
	this->likes = get_boolean_value( data.at("likes") );
	this->link_author = get_string_value( data.at("link_author") );
	this->link_permalink = get_string_value( data.at("link_permalink") );
	this->link_title = get_string_value(data.at("link_title"));
	this->mod_note = get_string_value(data.at("mod_note"));
	this->mod_reason_by = get_string_value( data.at("mod_reason_by"));
	this->mod_reason_title = get_string_value( data.at("mod_reason_title"));
	nlohmann::json mod_reports = data.at("mod_reports");
	for( auto& elem : mod_reports ) {
		this->mod_reports.push_back( elem.get<std::string>() );
	}
	
	this->name = get_string_value( data.at("name") );
	this->num_comments = get_integer_value( data.at("num_comments") );
	this->num_reports = get_integer_value( data.at("num_reports") );
	this->parent_id = get_string_value( data.at("parent_id") );
	this->over18 = get_boolean_value( data.at("over18") );
	this->permalink = get_string_value( data.at("permalink") );
	this->quarantine = get_boolean_value( data.at("quarantine") );
	this->removal_reason = get_string_value( data.at("removal_reason") );
	nlohmann::json removal_reasons = data.at("removal_reasons");
	if( !removal_reasons.is_null() ) {
		for( auto& elem : removal_reasons ) {
			this->removal_reasons.push_back( elem.get<std::string>() );
		}
	}
	this->saved = get_boolean_value( data.at("saved") );
	this->score = get_integer_value( data.at("score") );
	this->score_hidden = get_boolean_value( data.at("score_hidden") );
	this->stickied = get_boolean_value( data.at("stickied") );
	this->subreddit = get_string_value( data.at("subreddit") );
	this->subreddit_id = get_string_value( data.at("subreddit_id") );
	this->subreddit_name_prefixed = get_string_value( data.at("subreddit_name_prefix") );
	this->ups = get_integer_value( data.at("ups") );
	nlohmann::json user_reports = data.at("user_reports");
	if( !user_reports.is_null() ) {
		for( auto& elem : user_reports ) {
			this->user_reports.push_back(elem.get<std::string>());
		}
	}
							
}
