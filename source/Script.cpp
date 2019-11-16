#include "vunsur/Script.hpp"

namespace Vunsur
{
  ScriptAccess::ScriptAccess(std::string client_id, std::string secret, std::string user_agent, std::string username, std::string password)
  {
    this->client_id = client_id;
    this->secret = secret;
    this->user_agent = user_agent;
    this->username = username;
    this->password = password;
  }
  State AuthorizeWithReddit()
  {
    CURL* handle;
    std::string rdata, hdata;
    State s;

    handle = curl_easy_init();
    if(handle)
    {
      curl_easy_setopt(handle, CURLOPT_URL, "https://oauth.reddit.com/access_token");
      curl_easy_setopt(handle, CURLOPT_POST, 1L);
      curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(handle, CURLOPT_WRITEDATA, &rdata);
      //curl_easy_setopt(handle, CURLOPT_HEADERDATA, &hdata);
      curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &writedat);

      #ifdef _DEBUG
  	 	curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
  		#endif

  		s.result = curl_easy_perform(handle);
  		curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &s.code);
  		curl_easy_cleanup(handle);

      std::fstream("i-out.txt", std::ios::out) << rdata;

    }
    return s;
  }
}
