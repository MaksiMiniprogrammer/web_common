#include <web_common/http/http_header.h>

#include <algorithm>
#include <cctype>

namespace web
{
namespace http
{

std::string HttpHeader::NormalizeName(const std::string& name) const
{
    if (name.empty())
    {
        return std::string();
    }
    
    const std::string dropChars = " \t\n";
    size_t first = name.find_first_not_of(dropChars);
    if (first == std::string::npos) return std::string();
    size_t last = name.find_last_not_of(dropChars);
    
    std::string result = name.substr(first, (last - first + 1));
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
        
    return result;
}

std::string HttpHeader::NormalizeValue(const std::string& value) const
{
    if (value.empty()) 
    {
        return std::string();
    }

    const std::string dropChars = " \t\n";

    size_t first = value.find_first_not_of(dropChars);
    if (first == std::string::npos) 
    {
        return std::string();
    }
    size_t last = value.find_last_not_of(dropChars);
    return value.substr(first, (last - first + 1));
}

void HttpHeader::Set(const std::string& name, const std::string& value)
{
    std::string cleanName = NormalizeName(name);
    if (cleanName.empty())
    {
        return;
    }

    std::string cleanValue = NormalizeValue(value);
    
    headers_[cleanName] = std::move(cleanValue);
}

std::string HttpHeader::Get(const std::string& name) const
{
    std::string cleanName = NormalizeName(name);
    if (cleanName.empty() || headers_.empty())
    {
        return std::string();
    }

    auto it = headers_.find(cleanName);
    if (it != headers_.end())
    {
        return it->second;
    }
    return std::string();
}

bool HttpHeader::Has(const std::string& name) const
{
    std::string cleanName = NormalizeName(name);
    if (cleanName.empty() || headers_.empty())
    {
        return false;
    }
    return headers_.find(cleanName) != headers_.end();
}

void HttpHeader::Remove(const std::string& name)
{
    std::string cleanName = NormalizeName(name);
    if (cleanName.empty() || headers_.empty())
    {
        return;
    }
    headers_.erase(cleanName);
}

void HttpHeader::Clear()
{
    headers_.clear();
}

} // namespace http
} // namespace web