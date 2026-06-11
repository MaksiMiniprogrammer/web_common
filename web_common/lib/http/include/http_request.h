#pragma once

#ifndef WEB_COMMON_LIB_HTTP_HTTP_REQUEST_H_
#define WEB_COMMON_LIB_HTTP_HTTP_REQUEST_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <cstdint>

#include <web_common/http/http_method.h>
#include <web_common/http/http_version.h>
#include <web_common/http/http_header.h>

#include <web_common/utils/endpoint.h>

/**
 * @file http_request.h
 * @brief Определение класса HttpRequest для представления контекста входящего HTTP-запроса.
 */

namespace web
{
namespace http
{

/**
 * @class HttpRequest
 * @brief Класс, инкапсулирующий все данные входящего HTTP-запроса (метод, путь, заголовки, тело).
 */
class HttpRequest
{
public:
    /**
     * @brief Конструктор по умолчанию. Инициализирует перечисления значениями UNKNOWN.
     */
    HttpRequest();
    
    /**
     * @brief Деструктор по умолчанию.
     */
    ~HttpRequest() = default;

    HttpRequest(const HttpRequest&) = default;
    HttpRequest& operator=(const HttpRequest&) = default;
    HttpRequest(HttpRequest&&) noexcept = default;
    HttpRequest& operator=(HttpRequest&&) noexcept = default;
    
    HttpMethodUtil::HttpMethod GetMethod() const;
    void SetMethod(HttpMethodUtil::HttpMethod method);

    HttpVersionUtil::HttpVersion GetVersion() const;
    void SetVersion(HttpVersionUtil::HttpVersion version);

    const std::string& GetPath() const;
    void SetPath(const std::string& path);

    const std::string& GetRawQuery() const;
    void SetRawQuery(const std::string& query);

    const utils::NetworkEndpoint& GetClientEndpoint() const;
    void SetClientEndpoint(const utils::NetworkEndpoint& endpoint);

    const HttpHeader& GetHeaders() const;
    HttpHeader& GetHeaders();

    void SetQueryParam(const std::string& key, const std::string& value);
    std::string GetQueryParam(const std::string& key) const;
    bool HasQueryParam(const std::string& key) const;


    void SetBody(std::string body);
    void SetBody(std::vector<uint8_t> body);

    bool IsTextBody() const;
    bool IsBinaryBody() const;

    /**
     * @brief Безопасно извлекает текстовое тело запроса.
     * @return Строка с телом. Если тело бинарное или пустое — возвращает пустую строку.
     */
    std::string GetTextBody() const;

    /**
     * @brief Безопасно извлекает бинарное тело запроса.
     * @return Вектор байт. Если тело текстовое — возвращает пустой вектор.
     */
    std::vector<uint8_t> GetBinaryBody() const;

private:
    // Явная безопасная инициализация перечислений
    HttpMethodUtil::HttpMethod method_ = HttpMethodUtil::HttpMethod::UNKNOWN;
    HttpVersionUtil::HttpVersion version_ = HttpVersionUtil::HttpVersion::UNKNOWN;
    
    std::string path_;       ///< URL-путь запроса (например, "/api/v1/user").
    std::string rawQuery_;   ///< Строка параметров до парсинга (например, "id=42&sort=desc").
    utils::NetworkEndpoint clientEndpoint_;   ///< Полная информация о сетевой точке клиента.
    
    std::unordered_map<std::string, std::string> queryUrlParams_; ///< Карты распарсенных URL-параметров.
    
    HttpHeader headers_;     ///< Объект класса HttpHeader для метаданных.
    
    std::variant<std::string, std::vector<uint8_t>> body_; ///< Тело запроса (Текст или Бинарные байты).
};

} // namespace http
} // namespace web

#endif // WEB_COMMON_LIB_HTTP_HTTP_REQUEST_H_
