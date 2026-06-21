#pragma once

#ifndef WEB_COMMON_LIB_HTTP_HTTP_FACTORY_H_
#define WEB_COMMON_LIB_HTTP_HTTP_FACTORY_H_

#include <string>
#include <vector>
#include <cstdint>

#include <web_common/http/http_response.h>
#include <web_common/http/http_request.h>
#include <web_common/http/http_url.h>
#include <web_common/http/http_status.h>

namespace web
{
namespace http
{

class HttpFactory
{
public:

    HttpFactory() = delete;

    static HttpResponse CreateJsonResponse(HttpStatus status, std::string body);

    static HttpResponse CreateJsonResponse(HttpStatus status, std::vector<uint8_t> body);

    static HttpRequest ParseRequest(const std::string& rawRequest);

    static HttpUrl ParseUrl(const std::string& urlStr);
    
    static HttpResponse CreateErrorJsonResponse(http::HttpStatus status, const std::string& message);
};

}
}

#endif