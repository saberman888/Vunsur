#ifndef COMMENT_HPP
#define COMMENT_HPP

// Vunsur/base
#include "base/BaseThing.hpp"
#include "base/Votable.hpp"
#include "base/Created.hpp"
#include "base/Types.hpp"
// Root
#include "Error.hpp"
#include "vujson.hpp"
#include "source/vujson.cpp"
#include "condition.hpp"

#include <string>
#include "json.hpp"

class Comment : public BaseThing, public Votable, public Created {
	public:	
		bool approved;
		long approved_at_utc;
		std::string approved_by;
		bool archived;
		std::string author; // can be nulled
		std::string author_flair_css_class; // can be nulled
		std::string author_flair_text; // can be nulled
		long banned_at_utc; // can be nulled
		std::string banned_by; // can be nulled
		std::string body;
		std::string body_html;
		bool can_guild;
		bool can_mod_post;
		bool collapsed;
		std::string collapsed_reason; // can be nulled
		int controversiality;
		int depth;
		std::string distinguished; // can be nulled
		bool edited;
		int gilded;
		bool ignore_reports;
		bool is_submitter;
		std::string link_id;
		std::vector< std::string > mod_reports;
		std::string name;
		int num_reports;
		std::string parent_id;
		std::string removal_reason; // can be nulled
		bool removed;
		//std::vector< Comment* > replies;
		//std::vector< std::string > removal_reason; 
		bool saved;
		int score;
		bool score_hidden;
		bool spam;
		bool stickied;
		std::string subreddit;
		std::string subreddit_id;
		std::string subreddit_name_prefixed;
		std::string restricted_type;
		std::vector< std::string > user_reports;
		void convert_json_to_comment(Status& s, std::string json);
};

//Comment* convert_json_to_comment(Status& s, std::string json);
#endif
