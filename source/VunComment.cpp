
#include "subreddit/comments/VunComment.hpp"
#include <iostream>

VunComment::VunComment(nlohmann::json src)
{
	this->read(src);
}

VunComment::VunComment()
{

}

void VunComment::get_replies(nlohmann::json& src)
{
	if (!src.is_string() && src.is_array())
	{
		for (auto& elem : src)
		{
			nlohmann::json data = elem.at("data");
			nlohmann::json kind = data.at("kind");

			std::string Kind = kind.get<std::string>();

			VunComment* vc = new VunComment();
			if (!vc)
			{
				std::cerr << "Error: Failed to allocate a VunComment instance" << std::endl;
				exit(EXIT_FAILURE);
			}

			if (Kind == "t1")
			{
				vc->source.kind = Comment;
				vc->read(elem);
				this->replies.push_back(vc);
			}
			else if (Kind == "more") {
				vc->source.kind = More;

				nlohmann::json parent_id_json = data.at("parent_id");
				std::string parent_id = parent_id_json.get<std::string>();
				vc->source.parent_id = parent_id;
				vc->source.depth = get_integer_value(data.at("depth"));
				vc->source.name = "t1";
				std::string id = parent_id.substr(3, parent_id.size());

			}
		}
	}
}

void VunComment::read(nlohmann::json&  src)
{
	nlohmann::json data = src.at("data");
	
	this->source.approved_at_utc = get_long_value( data.at("approved_at_utc") );
	//this->source.approved = get_boolean_value( data.at("approved") );
	this->source.approved_by = get_string_value( data.at("approved_by") );
	this->source.archived =  get_boolean_value( data.at("archived") );
	this->source.author = get_string_value( data.at("author") );
	this->source.author_flair_css_class = get_string_value( data.at("author_flair_css_class") );
	this->source.author_flair_text = get_string_value( data.at("author_flair_text") );
	this->source.banned_at_utc = get_long_value( data.at("banned_at_utc") );
	this->source.banned_by = get_string_value( data.at("banned_by") );
	this->source.body = get_string_value( data.at("body") );
	this->source.body_html = get_string_value( data.at("body_html") );
	this->source.can_gild = get_boolean_value( data.at("can_gild") );
	this->source.can_mod_post = get_boolean_value( data.at("can_mod_post") );
	this->source.collapsed = get_boolean_value( data.at("collapsed") );
	this->source.collapsed_reason = get_string_value( data.at("collapsed_reason") );
	this->source.controversiality = get_integer_value( data.at("controversiality") );
	this->source.created = get_long_value( data.at("created") );
	this->source.created_utc = get_long_value( data.at("created_utc"));
	if( does_value_exist(data, "depth"))
		this->source.depth = get_integer_value( data.at("depth") );
	this->source.distinguished = get_string_value( data.at("distinguished") );
	this->source.downs = get_integer_value( data.at("downs") );
	this->source.edited = get_boolean_value( data.at("edited") );
	this->source.gilded = get_integer_value( data.at("gilded") );
	if( does_value_exist(data, "ignore_reports"))
		this->source.ignore_reports = get_boolean_value( data.at("ignore_reports") );
	this->source.is_submitter = get_boolean_value( data.at("is_submitter") );
	this->source.link_id = get_string_value( data.at("link_id") );
	this->source.likes = get_boolean_value( data.at("likes") );
	this->source.link_author = get_string_value( data.at("link_author") );
	this->source.link_permalink = get_string_value( data.at("link_permalink") );
	this->source.link_title = get_string_value(data.at("link_title"));
	this->source.mod_note = get_string_value(data.at("mod_note"));
	this->source.mod_reason_by = get_string_value( data.at("mod_reason_by"));
	this->source.mod_reason_title = get_string_value( data.at("mod_reason_title"));
	nlohmann::json mod_reports = data.at("mod_reports");
	for( auto& elem : mod_reports ) {
		this->source.mod_reports.push_back( elem.get<std::string>() );
	}
	
	this->source.name = get_string_value( data.at("name") );
	this->source.num_comments = get_integer_value( data.at("num_comments") );
	this->source.num_reports = get_integer_value( data.at("num_reports") );
	this->source.parent_id = get_string_value( data.at("parent_id") );
	this->source.over18 = get_boolean_value( data.at("over18") );
	this->source.permalink = get_string_value( data.at("permalink") );
	this->source.quarantine = get_boolean_value( data.at("quarantine") );
	this->source.removal_reason = get_string_value( data.at("removal_reason") );
	if (does_value_exist(data, "removal_reasons")) {
		nlohmann::json removal_reasons = data.at("removal_reasons");
		if (!removal_reasons.is_null()) {
			for (auto& elem : removal_reasons) {
				this->source.removal_reasons.push_back(elem.get<std::string>());
			}
		}
	}
	this->source.saved = get_boolean_value( data.at("saved") );
	this->source.score = get_integer_value( data.at("score") );
	this->source.score_hidden = get_boolean_value( data.at("score_hidden") );
	this->source.stickied = get_boolean_value( data.at("stickied") );
	this->source.subreddit = get_string_value( data.at("subreddit") );
	this->source.subreddit_id = get_string_value( data.at("subreddit_id") );
	this->source.subreddit_name_prefixed = get_string_value( data.at("subreddit_name_prefixed") );
	this->source.ups = get_integer_value( data.at("ups") );
	nlohmann::json user_reports = data.at("user_reports");
	if( !user_reports.is_null() ) {
		for( auto& elem : user_reports ) {
			this->source.user_reports.push_back(elem.get<std::string>());
		}
	}
}

size_t VunComment::size() {
	return this->replies.size();
}

CommentSource& VunComment::operator~()
{
	return this->source;
}
