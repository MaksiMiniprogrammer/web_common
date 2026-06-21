#pragma once

#ifndef WEB_COMMON_LIB_SERVER_COMMON_H_
#define WEB_COMMON_LIB_SERVER_COMMON_H_

#include <web_common/http/http_response.h>
#include <web_common/http/http_request.h>

#include <functional>

namespace web
{
namespace server
{

using HandleRequest = std::function<http::HttpResponse(const http::HttpRequest&)>;

struct RouteKey
{
    http::HttpMethodUtil::HttpMethod method;
    std::string path;

    bool operator==(const RouteKey& other) const 
    {
        return method == other.method && path == other.path;
    }
};

struct RouteKeyHasher 
{
    std::size_t operator()(const RouteKey& k) const 
    {
        std::size_t h1 = std::hash<std::string>{}(k.path);
        std::size_t h2 = std::hash<uint8_t>{}(static_cast<uint8_t>(k.method));
        return h1 ^ (h2 << 1);
    }
};

using RoutesStorage = std::unordered_map<RouteKey, HandleRequest, RouteKeyHasher>;

}
}

#endif // WEB_COMMON_LIB_SERVER_COMMON_H_