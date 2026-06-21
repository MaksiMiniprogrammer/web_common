#include <web_common/http/http_url.h>
#include <sstream>
#include <utility>

namespace web
{
namespace http
{

HttpUrl::HttpUrl(std::string pathStr, std::string queryStr, std::unordered_map<std::string, std::string> params)
: path(std::move(pathStr))
, rawQuery(std::move(queryStr))
, queryParams(std::move(params))
{
}

bool HttpUrl::IsEmpty() const
{
    return path.empty() && rawQuery.empty();
}

bool HttpUrl::HasParam(const std::string& key) const
{
    return queryParams.find(key) != queryParams.end();
}

std::string HttpUrl::GetParam(const std::string& key) const
{
    auto it = queryParams.find(key);
    return (it != queryParams.end()) ? it->second : std::string();
}

HttpUrl HttpUrl::FromString(const std::string& rawUrl)
{
    if (rawUrl.empty())
    {
        return HttpUrl();
    }

    std::string parsedPath;
    std::string parsedQuery;
    std::unordered_map<std::string, std::string> parsedParams;

    size_t questionMark = rawUrl.find('?');
    if (questionMark != std::string::npos)
    {
        parsedPath = rawUrl.substr(0, questionMark);
        parsedQuery = rawUrl.substr(questionMark + 1);

        if (!parsedQuery.empty())
        {
            std::istringstream queryStream(parsedQuery);
            std::string pair;

            while (std::getline(queryStream, pair, '&'))
            {
                if (pair.empty()) continue;

                size_t eq = pair.find('=');
                if (eq != std::string::npos)
                {
                    std::string key = pair.substr(0, eq);
                    std::string value = pair.substr(eq + 1);
                    if (!key.empty())
                    {
                        parsedParams[std::move(key)] = std::move(value);
                    }
                }
                else
                {
                    parsedParams[pair] = std::string();
                }
            }
        }
    }
    else
    {
        parsedPath = rawUrl;
    }

    return HttpUrl(std::move(parsedPath), std::move(parsedQuery), std::move(parsedParams));
}

} // namespace http
} // namespace web
