#include <web_common/server/dispatcher.h>
#include <web_common/http/http_factory.h>
#include <web_common/http/http_status.h>

namespace web
{
namespace server
{

Dispatcher::Dispatcher()
: routes_()
{}

void Dispatcher::AddRoute(http::HttpMethodUtil::HttpMethod method, const std::string& path, HandleRequest handler)
{
    if (method == http::HttpMethodUtil::HttpMethod::UNKNOWN || path.empty() || !handler)
    {
        return;
    }

    RouteKey key{method, path};
    routes_[key] = std::move(handler);
}

http::HttpResponse Dispatcher::Dispatch(http::HttpRequest request)
{
    RouteKey searchKey{request.GetMethod(), request.GetPath()};

    auto it = routes_.find(searchKey);
    if (it != routes_.end())
    {
        return it->second(request);
    }

    return http::HttpFactory::CreateErrorJsonResponse(
        http::HttpStatus::NOT_FOUND, 
        "The requested endpoint does not exist on this server."
    );
}

}
}