#pragma once

#ifndef WEB_COMMON_LIB_SERVER_DISPATCHER_H_
#define WEB_COMMON_LIB_SERVER_DISPATCHER_H_

#include <web_common/http/http_response.h>
#include <web_common/http/http_request.h>

#include <web_common/server/common.h>
#include <web_common/utils/singleton.h>

namespace web
{
namespace server
{

class Dispatcher : public utils::Singleton<Dispatcher>
{
private:

    friend class utils::Singleton<Dispatcher>;

    Dispatcher();
    ~Dispatcher() = default;

public:

    void AddRoute(http::HttpMethodUtil::HttpMethod method, const std::string& path, HandleRequest handler);

    http::HttpResponse Dispatch(http::HttpRequest request);

private:

    RoutesStorage routes_;
};

}
}

#endif // WEB_COMMON_LIB_SERVER_DISPATCHER_H_