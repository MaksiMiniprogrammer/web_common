#include <web_common/http/http_status.h>

namespace web
{
namespace http
{

std::string HttpStatusUtil::ToString(HttpStatus status)
{
    switch (status)
    {
        // 1xx
        case HttpStatus::CONTINUE:                  return "Continue";
        case HttpStatus::SWITCHING_PROTOCOLS:       return "Switching Protocols";

        // 2xx
        case HttpStatus::OK:                        return "OK";
        case HttpStatus::CREATED:                   return "Created";
        case HttpStatus::ACCEPTED:                  return "Accepted";
        case HttpStatus::NO_CONTENT:                return "No Content";

        // 3xx
        case HttpStatus::MOVED_PERMANENTLY:          return "Moved Permanently";
        case HttpStatus::FOUND:                     return "Found";
        case HttpStatus::SEE_OTHER:                 return "See Other";
        case HttpStatus::NOT_MODIFIED:              return "Not Modified";
        case HttpStatus::TEMPORARY_REDIRECT:         return "Temporary Redirect";
        case HttpStatus::PERMANENT_REDIRECT:         return "Permanent Redirect";

        // 4xx
        case HttpStatus::BAD_REQUEST:               return "Bad Request";
        case HttpStatus::UNAUTHORIZED:              return "Unauthorized";
        case HttpStatus::FORBIDDEN:                 return "Forbidden";
        case HttpStatus::NOT_FOUND:                 return "Not Found";
        case HttpStatus::METHOD_NOT_ALLOWED:        return "Method Not Allowed";
        case HttpStatus::NOT_ACCEPTABLE:            return "Not Acceptable";
        case HttpStatus::REQUEST_TIMEOUT:           return "Request Timeout";
        case HttpStatus::CONFLICT:                  return "Conflict";
        case HttpStatus::GONE:                      return "Gone";
        case HttpStatus::PAYLOAD_TOO_LARGE:         return "Payload Too Large";
        case HttpStatus::UNSUPPORTED_MEDIA_TYPE:    return "Unsupported Media Type";
        case HttpStatus::TOO_MANY_REQUESTS:         return "Too Many Requests";

        // 5xx
        case HttpStatus::INTERNAL_SERVER_ERROR:     return "Internal Server Error";
        case HttpStatus::NOT_IMPLEMENTED:           return "Not Implemented";
        case HttpStatus::BAD_GATEWAY:               return "Bad Gateway";
        case HttpStatus::SERVICE_UNAVAILABLE:       return "Service Unavailable";
        case HttpStatus::GATEWAY_TIMEOUT:           return "Gateway Timeout";
        case HttpStatus::HTTP_VERSION_NOT_SUPPORTED: return "HTTP Version Not Supported";

        case HttpStatus::UNKNOWN:
        default:
            return "Unknown Status Code";
    }
}

std::string HttpStatusUtil::ToString(uint16_t status)
{
    return ToString(ToStatusClass(status));
}

uint16_t HttpStatusUtil::ToUInt16(HttpStatus status)
{
    return static_cast<uint16_t>(status);
}

HttpStatus HttpStatusUtil::ToStatusClass(uint16_t status)
{
    switch (status)
    {
        case 100: return HttpStatus::CONTINUE;
        case 101: return HttpStatus::SWITCHING_PROTOCOLS;
        
        case 200: return HttpStatus::OK;
        case 201: return HttpStatus::CREATED;
        case 202: return HttpStatus::ACCEPTED;
        case 204: return HttpStatus::NO_CONTENT;
        
        case 301: return HttpStatus::MOVED_PERMANENTLY;
        case 302: return HttpStatus::FOUND;
        case 303: return HttpStatus::SEE_OTHER;
        case 304: return HttpStatus::NOT_MODIFIED;
        case 307: return HttpStatus::TEMPORARY_REDIRECT;
        case 308: return HttpStatus::PERMANENT_REDIRECT;
        
        case 400: return HttpStatus::BAD_REQUEST;
        case 401: return HttpStatus::UNAUTHORIZED;
        case 403: return HttpStatus::FORBIDDEN;
        case 404: return HttpStatus::NOT_FOUND;
        case 405: return HttpStatus::METHOD_NOT_ALLOWED;
        case 406: return HttpStatus::NOT_ACCEPTABLE;
        case 408: return HttpStatus::REQUEST_TIMEOUT;
        case 409: return HttpStatus::CONFLICT;
        case 410: return HttpStatus::GONE;
        case 413: return HttpStatus::PAYLOAD_TOO_LARGE;
        case 415: return HttpStatus::UNSUPPORTED_MEDIA_TYPE;
        case 429: return HttpStatus::TOO_MANY_REQUESTS;
        
        case 500: return HttpStatus::INTERNAL_SERVER_ERROR;
        case 501: return HttpStatus::NOT_IMPLEMENTED;
        case 502: return HttpStatus::BAD_GATEWAY;
        case 503: return HttpStatus::SERVICE_UNAVAILABLE;
        case 504: return HttpStatus::GATEWAY_TIMEOUT;
        case 505: return HttpStatus::HTTP_VERSION_NOT_SUPPORTED;
        
        default: return HttpStatus::UNKNOWN;
    }
}

} // namespace http
} // namespace web
