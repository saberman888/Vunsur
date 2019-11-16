#pragma once

#include "Access.hpp"
#include "vujson.hpp"
#include "State.hpp"

namespace Vunsur {
  class ScriptAccess : protected Access
  {
    public:
      ScriptAccess(std::string client_id, std::string secret, std::string user_agent, std::string username, std::string password);
      State AuthorizeWithReddit();
    private:
      bool refresh;
      void obtain_token();
  };
}
