#pragma once

#include <string>
#include "curl/curl.h"

namespace Vunsur{
  class State
  {
    public:
      State(){}
      State(int code, std::string message) { this->code = code; this->message = message;}
      int code;
      CURLcode result;
      std::string message;
      std::string error() { return curl_easy_strerror(result);}
      bool IsGood() { return ((code == 200)&&(result == CURLE_OK));}
  };
}
