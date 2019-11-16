#pragma once

#include "curl/curl.h"
#include <string>
#include <chrono>
#include <ctime>
#include <thread>

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
    private:
      std::vector<std::string> permission_string_list;
    protected:
      std::string client_id, secret;
      std::string username, password;
      std::string user_agent;
      std::string scope;

      void gen_permissions();
    public:
      Access();
      std::string token, tokentype;
      std::vector<Permissions> perms;

      virtual void obtain_token();

      // These variables and functions are a way to keep track of session requests
      int requests_done_in_60, total_requests_in_session;
      std::chrono::system_clock::time_point now, then, mnow, mthen;
      void reset_minute_clock();
      void is_mtime_up();
      bool is_time_up();
      void tick();
      
      void operator<<(const Access& a, const Permission p);

  };

  bool init();
  bool init(CURLcode& result);
  void cleanup();
}
