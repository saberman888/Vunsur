#ifndef COMMENT_HPP
#define COMMENT_HPP

// Vunsur/base
#include "base/BaseThing.hpp"
#include "base/Votable.hpp"
#include "base/Created.hpp"
#include "base/Types.hpp"
// Root

#include <string>
#include <vector>



class CommentSource : public BaseThing, public Votable, public Created {
	public:	
		bool approved;
		long approved_at_utc;
		std::string approved_by;
		bool archived;
		std::string author; // can be nulled
		std::string author_flair_css_class; // can be nulled
		std::string author_flair_text; // can be nulled

		/*
		TODO
		std::string author_flair_background_color;
		std::string author_flair_richtext;
		std::string author_flair_text;
		std::string author_flair_text_color;
		std::string author_flair_type;
		*/

		long banned_at_utc; // can be nulled
		std::string banned_by; // can be nulled
		std::string body;
		std::string body_html;

		bool can_gild;
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
		std::string link_author;
		std::string link_permalink;
		std::string link_title;
		std::string url;

		std::string mod_note;
		std::string mod_reason_by;
		std::string mod_reason_title;
		std::vector< std::string > mod_reports;

		int num_comments;
		int num_reports;
		std::string name;
		bool no_follow;


		bool over18;

		std::string parent_id;
		std::string permalink;

		bool quarantine;

		std::string removal_reason; // can be nulled
		bool removed;
		std::vector< std::string > removal_reasons;
		std::vector< std::string > report_reasons;
		std::string rte_mode;
		std::string restricted_type;

		bool saved;
		int score;
		bool score_hidden;
		bool send_replies;
		bool spam;
		bool stickied;
		std::string subreddit;
		std::string subreddit_id;
		std::string subreddit_name_prefixed;
		std::string subreddit_type;


		std::vector< std::string > user_reports;
};

#endif
