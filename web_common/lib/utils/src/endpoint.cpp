#include <web_common/utils/endpoint.h>
#include <boost/asio/ip/address.hpp>
#include <sstream>
#include <algorithm>

namespace web
{
namespace utils
{

NetworkEndpoint::NetworkEndpoint(std::string ipAddress, uint16_t portNumber)
: ip(std::move(ipAddress))
, port(portNumber)
{
}

bool NetworkEndpoint::IsEmpty() const
{
    return ip.empty();
}

bool NetworkEndpoint::IsValid() const
{
    if (ip.empty()) return false;
    
    boost::system::error_code ec;
    boost::asio::ip::make_address(ip, ec);
    
    return !ec;
}

bool NetworkEndpoint::IsIPv4() const
{
    if (ip.empty()) return false;
    
    boost::system::error_code ec;
    auto addr = boost::asio::ip::make_address(ip, ec);
    return !ec && addr.is_v4();
}

bool NetworkEndpoint::IsIPv6() const
{
    if (ip.empty()) return false;
    
    boost::system::error_code ec;
    auto addr = boost::asio::ip::make_address(ip, ec);
    return !ec && addr.is_v6();
}

std::string NetworkEndpoint::ToString() const
{
    if (ip.empty()) return std::string();

    std::stringstream ss;
    if (IsIPv6())
    {
        ss << "[" << ip << "]:" << port;
    }
    else
    {
        ss << ip << ":" << port;
    }
    return ss.str();
}

NetworkEndpoint NetworkEndpoint::FromString(const std::string& rawEndpoint)
{
    if (rawEndpoint.empty())
    {
        return NetworkEndpoint();
    }

    std::string parsedIp;
    uint16_t parsedPort = 0;

    if (rawEndpoint.front() == '[')
    {
        size_t closeBracket = rawEndpoint.find(']');
        if (closeBracket != std::string::npos)
        {
            parsedIp = rawEndpoint.substr(1, closeBracket - 1);
            
            size_t colon = rawEndpoint.find(':', closeBracket);
            if (colon != std::string::npos && colon + 1 < rawEndpoint.size())
            {
                parsedPort = static_cast<uint16_t>(std::stoul(rawEndpoint.substr(colon + 1)));
            }
        }
    }
    else
    {
        size_t colon = rawEndpoint.find(':');
        if (colon != std::string::npos)
        {
            parsedIp = rawEndpoint.substr(0, colon);
            if (colon + 1 < rawEndpoint.size())
            {
                parsedPort = static_cast<uint16_t>(std::stoul(rawEndpoint.substr(colon + 1)));
            }
        }
        else
        {
            parsedIp = rawEndpoint;
        }
    }

    return NetworkEndpoint(parsedIp, parsedPort);
}

} // namespace http
} // namespace web
