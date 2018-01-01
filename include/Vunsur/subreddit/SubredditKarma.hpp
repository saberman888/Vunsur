#ifndef SUBREDDIT_KARMA_HPP
#define SUBREDDIT_KARMA_HPP

// The structure used to store data from the the user's
// karma by subreddit

typedef struct sbkarma
{
	int comment_karma;
	int link_karma;
	std::string subreddit;
}SubredditKarma;

#endif
