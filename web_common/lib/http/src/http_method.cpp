#include <web_common/http/http_method.h>

namespace web
{
namespace http
{

std::string HttpMethodUtil::ToString( HttpMethod method )
{
    switch (method)
    {
        case HttpMethod::GET:
            return "GET";
        case HttpMethod::PUT:
            return "PUT";
        case HttpMethod::POST:
            return "POST";
        case HttpMethod::DELETE:
            return "DELETE";
        case HttpMethod::UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

std::string HttpMethodUtil::ToString( uint8_t method )
{
    // Повторно используем первый ToString, транслируя число в класс
    return ToString(ToMethodClass(method));
}

HttpMethodUtil::HttpMethod HttpMethodUtil::FromString( const std::string& method )
{
    if (method == "GET")    return HttpMethod::GET;
    if (method == "PUT")    return HttpMethod::PUT;
    if (method == "POST")   return HttpMethod::POST;
    if (method == "DELETE") return HttpMethod::DELETE;
    return HttpMethod::UNKNOWN;
}

uint8_t HttpMethodUtil::ToUInt8( HttpMethodUtil::HttpMethod method )
{
    return static_cast<uint8_t>(method);
}

HttpMethodUtil::HttpMethod HttpMethodUtil::ToMethodClass( uint8_t method )
{
    switch (method)
    {
        case static_cast<uint8_t>(HttpMethod::GET):
            return HttpMethod::GET;
        case static_cast<uint8_t>(HttpMethod::PUT):
            return HttpMethod::PUT;
        case static_cast<uint8_t>(HttpMethod::POST):
            return HttpMethod::POST;
        case static_cast<uint8_t>(HttpMethod::DELETE):
            return HttpMethod::DELETE;
        default:
            return HttpMethod::UNKNOWN;
    }
}

} // namespace http
} // namespace web
