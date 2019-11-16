#include "vunsur/Access.hpp"

namespace Vunsur {

  Access::Access() : requests_done_in_60(0) total_requests_in_session(0), scope("scope=")
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
      for(std::string : permission_string_list)
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
  		restart_minute_clock();
  	} else if (mnow >= mthen) {
  		std::clog << "Restarting the minute clock!" << std::endl;
  		restart_minute_clock();
    }
  }

  void Access::is_time_up()
  {
    if(now >= then)
      return true;
    return false;
  }

  void Access:tick()
  {
    requests_done += 1;
  	if (now < then) {
  		this->request_done_in_current_minute += 1;
  	}
  }

  bool init()
  {
    CURLcode result = curl_global_init();
    return (result == CURLE_OK);
  }

  bool init(CURLcode& result)
  {
    result = curl_global_init();
    return (result == CURLE_OK);
  }


  void cleanup()
  {
    curl_global_cleanup();
  }

  void Access::operator<<(const Access& a, const Permission p)
  {
    a.perms.push_back(p);
  }

}
