#include <web_common/http/http_version.h>

namespace web
{
namespace http
{

std::string HttpVersionUtil::ToString( HttpVersion version )
{
    switch (version)
    {
        case HttpVersion::HTTP_0_9:
            return "HTTP/0.9";
        case HttpVersion::HTTP_1_0:
            return "HTTP/1.0";
        case HttpVersion::HTTP_1_1:
            return "HTTP/1.1";
        case HttpVersion::HTTP_2_0:
            return "HTTP/2.0";
        case HttpVersion::HTTP_3_0:
            return "HTTP/3.0";
        case HttpVersion::UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

std::string HttpVersionUtil::ToString( uint8_t version )
{
    return ToString(ToVersionClass(version));
}

HttpVersionUtil::HttpVersion HttpVersionUtil::FromString( const std::string& version )
{
    if (version == "HTTP/1.1" || version == "HTTP/1.1") return HttpVersion::HTTP_1_1;
    if (version == "HTTP/2.0" || version == "HTTP/2")   return HttpVersion::HTTP_2_0;
    if (version == "HTTP/3.0" || version == "HTTP/3")   return HttpVersion::HTTP_3_0;
    if (version == "HTTP/1.0")                          return HttpVersion::HTTP_1_0;
    if (version == "HTTP/0.9")                          return HttpVersion::HTTP_0_9;
    return HttpVersion::UNKNOWN;
}

uint8_t HttpVersionUtil::ToUInt8( HttpVersionUtil::HttpVersion version )
{
    return static_cast<uint8_t>(version);
}

HttpVersionUtil::HttpVersion HttpVersionUtil::ToVersionClass( uint8_t version )
{
    switch (version)
    {
        case static_cast<uint8_t>(HttpVersion::HTTP_0_9):
            return HttpVersion::HTTP_0_9;
        case static_cast<uint8_t>(HttpVersion::HTTP_1_0):
            return HttpVersion::HTTP_1_0;
        case static_cast<uint8_t>(HttpVersion::HTTP_1_1):
            return HttpVersion::HTTP_1_1;
        case static_cast<uint8_t>(HttpVersion::HTTP_2_0):
            return HttpVersion::HTTP_2_0;
        case static_cast<uint8_t>(HttpVersion::HTTP_3_0):
            return HttpVersion::HTTP_3_0;
        default:
            return HttpVersion::UNKNOWN;
    }
}

} // namespace http
} // namespace web
