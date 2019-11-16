#pragma once

#include "curl/curl.h"
#include <string>
#include <chrono>
#include <ctime>
#include <vector>

#if defined(unix) || defined(_unix)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#else
#include <Synchapi.h>
#endif

namespace Vunsur {
  typedef enum e_permissions
  {
  	account = 0,
  	creddits,
  	edit,
  	flair,
  	history,
  	identity,
  	livemanage,
  	modconfig,
  	modcontributors,
  	modflair,
  	modlog,
  	modmail,
  	modothers,
  	modposts,
  	modself,
  	modtraffic,
  	modwiki,
  	mysubreddits,
  	privatemessages,
  	read,
  	report,
  	save,
  	structuredstyles,
  	submit,
  	subscribe,
  	vote,
  	wikiedit,
  	wikiread
  }Permission;

  class Access
  {
  public:
      std::string client_id, secret;
      std::string username, password;
      std::string user_agent;
      std::string scope;

      std::vector<std::string> permission_string_list;
      void gen_permissions();

      int rq_per_minute, max_rq_per_session;
      void set_rq_limit(int rq_per_60, int max_per_session);

      Access();
      std::string token, tokentype;
      std::vector<Permission> perms;

      virtual void obtain_token();

      // These variables and functions are a way to keep track of session requests
      int requests_done_in_60, total_requests_in_session;
      std::chrono::system_clock::time_point now, then, mnow, mthen;
      void reset_minute_clock();
      void is_mtime_up();
      bool is_time_up();
      void tick();

      friend Access& operator<<(Access& a, const Permission p);
  };
  Access& operator<<(Access& a, const Permission p);

  bool init();
  bool init(CURLcode& result);
  void cleanup();
}
