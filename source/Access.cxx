#include "vunsur/Access.hpp"

namespace Vunsur {

  Access::Access() : requests_done_in_60(0), total_requests_in_session(0), scope("scope=")
  {
    this->permission_string_list = {
      "account",
      "creddits",
      "edit",
      "flair",
      "history",
      "identity",
      "livemanage",
      "modconfig",
      "modcontributors",
      "modflair",
      "modlog",
      "modmail",
      "modothers",
      "modposts",
      "modself",
      "modtraffic",
      "modwiki",
      "mysubreddits",
      "privatemessages",
      "read",
      "report",
      "save",
      "structuredstyles",
      "submit",
      "subscribe",
      "vote",
      "wikiedit",
      "wikiread"
    };
  }

  void Access::gen_permissions()
  {
    // If it the perms is 0, then grant all permissions
    if(perms.empty())
    {
      for(std::string elem : permission_string_list)
      {
        scope += elem;
        scope += "%20";
      }
    } else {
      for(Permission p : perms)
      {
        scope += permission_string_list[(int)p];
        scope += "%20";
      }
    }
  }

  void Access::set_rq_limit(int rq_per_60, int max_per_session)
  {
    rq_per_minute = rq_per_60;
    max_rq_per_session = max_per_session;
  }
  void Access::reset_minute_clock()
  {
    std::chrono::minutes one_minute(1);
    mnow = std::chrono::system_clock::now();
    mthen = mnow + one_minute;
    requests_done_in_60 = 0;
  }

  void Access::is_mtime_up()
  {
    if(requests_done_in_60 == rq_per_minute) {
      // Stall then reset time
  		#ifdef _WIN32
  		Sleep(60000);
  		#elif _unix
  		usleep(60);
  		#else
  		usleep(60);
  		#endif
  		reset_minute_clock();
  	} else if (mnow >= mthen) {
  		reset_minute_clock();
    }
  }

  bool Access::is_time_up()
  {
    if(now >= then)
      return true;
    return false;
  }

  void Access::tick()
  {
    total_requests_in_session += 1;
  	if (now <= then) {
  		requests_done_in_60 += 1;
  	}
  }

  bool init()
  {
    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    return (result == CURLE_OK);
  }

  bool init(CURLcode& result)
  {
    result = curl_global_init(CURL_GLOBAL_ALL);
    return (result == CURLE_OK);
  }


  void cleanup()
  {
    curl_global_cleanup();
  }

  Access& operator<<(Access& a, const Permission p)
  {
    a.perms.push_back(p);
    return a;
  }

}
