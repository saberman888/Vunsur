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
}
