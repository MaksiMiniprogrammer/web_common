#include <web_common/http/http_response.h>
#include <utility>

namespace web
{
namespace http
{

HttpResponse::HttpResponse()
: version_(HttpVersionUtil::HttpVersion::HTTP_1_1)
, status_(HttpStatus::OK)
{
}

HttpVersionUtil::HttpVersion HttpResponse::GetVersion() const
{
    return version_;
}

void HttpResponse::SetVersion(HttpVersionUtil::HttpVersion version)
{
    version_ = version;
}

HttpStatus HttpResponse::GetStatus() const
{
    return status_;
}

void HttpResponse::SetStatus(HttpStatus status)
{
    status_ = status;
}

void HttpResponse::SetStatus(uint16_t statusCode)
{
    status_ = HttpStatusUtil::ToStatusClass(statusCode);
}

const HttpHeader& HttpResponse::GetHeaders() const
{
    return headers_;
}

HttpHeader& HttpResponse::GetHeaders()
{
    return headers_;
}

void HttpResponse::SetBody(std::string body)
{
    body_ = std::move(body);
}

void HttpResponse::SetBody(std::vector<uint8_t> body)
{
    body_ = std::move(body);
}

bool HttpResponse::IsTextBody() const
{
    return std::holds_alternative<std::string>(body_);
}

bool HttpResponse::IsBinaryBody() const
{
    return std::holds_alternative<std::vector<uint8_t>>(body_);
}

std::string HttpResponse::GetTextBody() const
{
    if (auto val = std::get_if<std::string>(&body_)) 
    {
        return *val;
    }
    return std::string();
}

std::vector<uint8_t> HttpResponse::GetBinaryBody() const
{
    if (auto val = std::get_if<std::vector<uint8_t>>(&body_)) 
    {
        return *val;
    }
    return std::vector<uint8_t>();
}

} // namespace http
} // namespace web
