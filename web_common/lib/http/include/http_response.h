#pragma once

#ifndef WEB_COMMON_LIB_HTTP_HTTP_RESPONSE_H_
#define WEB_COMMON_LIB_HTTP_HTTP_RESPONSE_H_

#include <string>
#include <vector>
#include <variant>
#include <cstdint>

#include <web_common/http/http_version.h>
#include <web_common/http/http_status.h>
#include <web_common/http/http_header.h>

/**
 * @file http_response.h
 * @brief Определение класса HttpResponse для формирования контекста HTTP-ответа.
 */
namespace web
{
namespace http
{

/**
 * @class HttpResponse
 * @brief Класс, инкапсулирующий все данные исходящего HTTP-ответа (версия, статус, заголовки, тело).
 */
class HttpResponse
{
public:
    /**
     * @brief Конструктор по умолчанию. Инициализирует статус как 200 OK.
     */
    HttpResponse();
    
    /**
     * @brief Деструктор по умолчанию.
     */
    ~HttpResponse() = default;

    HttpResponse(const HttpResponse&) = default;
    HttpResponse& operator=(const HttpResponse&) = default;
    HttpResponse(HttpResponse&&) noexcept = default;
    HttpResponse& operator=(HttpResponse&&) noexcept = default;

    HttpVersionUtil::HttpVersion GetVersion() const;
    void SetVersion(HttpVersionUtil::HttpVersion version);

    HttpStatus GetStatus() const;
    void SetStatus(HttpStatus status);
    void SetStatus(uint16_t statusCode);
    const HttpHeader& GetHeaders() const;
    HttpHeader& GetHeaders();

    void SetBody(std::string body);
    void SetBody(std::vector<uint8_t> body);

    bool IsTextBody() const;
    bool IsBinaryBody() const;

    std::string GetTextBody() const;
    std::vector<uint8_t> GetBinaryBody() const;

private:
    HttpVersionUtil::HttpVersion version_ = HttpVersionUtil::HttpVersion::HTTP_1_1; 
    HttpStatus status_ = HttpStatus::OK;                                          
    
    HttpHeader headers_;
    
    std::variant<std::string, std::vector<uint8_t>> body_;
};

} // namespace http
} // namespace web

#endif // WEB_COMMON_LIB_HTTP_HTTP_RESPONSE_H_
