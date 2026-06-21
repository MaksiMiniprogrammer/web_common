#include <web_common/http/http_factory.h>
#include <utility>
#include <sstream>
namespace web
{
namespace http
{

namespace config 
{
    inline const std::string CONNECTION_KEEP = "keep-alive";
    inline const std::string CONTENT_TYPE_JSON = "application/json; charset=utf-8";
#ifdef NDEBUG
    inline const std::string SERVER_NAME     = "WebCommonServer/1.0 (Release)";
#else
    inline const std::string SERVER_NAME     = "WebCommonServer/1.0 (Debug)";
#endif
}

namespace
{
    template <typename T>
    HttpResponse BuildJsonResponseBase(HttpStatus status, const std::string& contentType, T body)
    {
        HttpResponse response;
        response.SetStatus(status);
        
        auto& headers = response.GetHeaders();
        headers.Set("Server", config::SERVER_NAME);
        headers.Set("Content-Type", contentType);
        headers.Set("Content-Length", std::to_string(body.size()));
        headers.Set("Connection", config::CONNECTION_KEEP);
        
        response.SetBody(std::move(body));
        return response;
    }
} // namespace

HttpResponse HttpFactory::CreateJsonResponse(HttpStatus status, std::string body)
{
    return BuildJsonResponseBase(status, config::CONTENT_TYPE_JSON, std::move(body));
}

HttpResponse HttpFactory::CreateJsonResponse(HttpStatus status, std::vector<uint8_t> body)
{
    return BuildJsonResponseBase(status, config::CONTENT_TYPE_JSON, std::move(body));
}

HttpResponse HttpFactory::CreateErrorJsonResponse(http::HttpStatus status, const std::string& message)
{
    std::string jsonError = "{\"error\":\"" + http::HttpStatusUtil::ToString(status) + 
                            "\",\"message\":\"" + message + "\"}";

    return BuildJsonResponseBase(status, config::CONTENT_TYPE_JSON, std::move(jsonError));
}

HttpRequest HttpFactory::ParseRequest(const std::string& rawRequest)
{
    HttpRequest request;
    if (rawRequest.empty()) 
    {
        return request;
    }

    std::istringstream stream(rawRequest);
    std::string line;

    if (!std::getline(stream, line)) 
    {
        return request;
    }
    if (!line.empty() && line.back() == '\r') 
    {
        line.pop_back();
    }

    std::istringstream startLineStream(line);
    std::string rawMethod, rawUrlStr, rawVersion;
    if (!(startLineStream >> rawMethod >> rawUrlStr >> rawVersion)) 
    {
        return request;
    }

    request.SetMethod(HttpMethodUtil::FromString(rawMethod));
    request.SetVersion(HttpVersionUtil::FromString(rawVersion));

    HttpUrl url = ParseUrl(rawUrlStr);
    
    request.SetPath(std::move(url.path));
    request.SetRawQuery(std::move(url.rawQuery));
    
    for (auto&& [key, value] : url.queryParams)
    {
        request.SetQueryParam(key, value);
    }

    while (std::getline(stream, line) && line != "\r" && !line.empty())
    {
        if (line.back() == '\r') 
        {
            line.pop_back();
        }

        size_t colon = line.find(':');
        if (colon != std::string::npos)
        {
            std::string headerName = line.substr(0, colon);
            std::string headerValue = line.substr(colon + 1);
            
            request.GetHeaders().Set(headerName, headerValue);
        }
    }

    std::string body((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    if (!body.empty())
    {
        request.SetBody(std::move(body));
    }

    return request;
}

HttpUrl HttpFactory::ParseUrl(const std::string& urlStr)
{
    return HttpUrl::FromString(urlStr);
}

} // namespace http
} // namespace web
