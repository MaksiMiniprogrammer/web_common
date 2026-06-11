#include <web_common/http/http_request.h>
#include <utility>

namespace web
{
namespace http
{

HttpRequest::HttpRequest()
: method_(HttpMethodUtil::HttpMethod::UNKNOWN)
, version_(HttpVersionUtil::HttpVersion::UNKNOWN)
{
}

HttpMethodUtil::HttpMethod HttpRequest::GetMethod() const 
{ 
    return method_; 
}

void HttpRequest::SetMethod(HttpMethodUtil::HttpMethod method) 
{ 
    method_ = method; 
}

HttpVersionUtil::HttpVersion HttpRequest::GetVersion() const 
{ 
    return version_; 
}

void HttpRequest::SetVersion(HttpVersionUtil::HttpVersion version) 
{ 
    version_ = version; 
}

const std::string& HttpRequest::GetPath() const 
{ 
    return path_; 
}

void HttpRequest::SetPath(const std::string& path) 
{ 
    path_ = path; 
}

const std::string& HttpRequest::GetRawQuery() const 
{ 
    return rawQuery_; 
}

void HttpRequest::SetRawQuery(const std::string& query) 
{ 
    rawQuery_ = query; 
}

const utils::NetworkEndpoint& HttpRequest::GetClientEndpoint() const 
{ 
    return clientEndpoint_; 
}

void HttpRequest::SetClientEndpoint(const utils::NetworkEndpoint& endpoint) 
{ 
    clientEndpoint_ = endpoint; 
}


const HttpHeader& HttpRequest::GetHeaders() const 
{ 
    return headers_; 
}

HttpHeader& HttpRequest::GetHeaders() 
{ 
    return headers_; 
}

void HttpRequest::SetQueryParam(const std::string& key, const std::string& value)
{
    queryUrlParams_[key] = value;
}

std::string HttpRequest::GetQueryParam(const std::string& key) const
{
    auto it = queryUrlParams_.find(key);
    return (it != queryUrlParams_.end()) ? it->second : std::string();
}

bool HttpRequest::HasQueryParam(const std::string& key) const
{
    return queryUrlParams_.find(key) != queryUrlParams_.end();
}

void HttpRequest::SetBody(std::string body)
{
    body_ = std::move(body);
}

void HttpRequest::SetBody(std::vector<uint8_t> body)
{
    body_ = std::move(body);
}

bool HttpRequest::IsTextBody() const
{
    return std::holds_alternative<std::string>(body_);
}

bool HttpRequest::IsBinaryBody() const
{
    return std::holds_alternative<std::vector<uint8_t>>(body_);
}

std::string HttpRequest::GetTextBody() const
{
    if (auto val = std::get_if<std::string>(&body_)) 
    {
        return *val;
    }
    return std::string();
}

std::vector<uint8_t> HttpRequest::GetBinaryBody() const
{
    if (auto val = std::get_if<std::vector<uint8_t>>(&body_)) 
    {
        return *val;
    }
    return std::vector<uint8_t>();
}

} // namespace http
} // namespace web
