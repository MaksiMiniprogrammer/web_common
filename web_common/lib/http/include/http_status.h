#pragma once

#ifndef WEB_COMMON_LIB_HTTP_HTTP_STATUS_H_
#define WEB_COMMON_LIB_HTTP_HTTP_STATUS_H_

#include <cstdint>
#include <string>

/**
 * @file http_status.h
 * @brief Определение кодов ответов HTTP (Status Codes) и функций для их конвертации.
 */

namespace web
{
namespace http
{

/**
 * @enum HttpStatus
 * @brief Перечисление наиболее часто используемых кодов ответов HTTP.
 */
enum class HttpStatus : uint16_t
{
    UNKNOWN                         = 0,

    // 1xx Информационные
    CONTINUE                        = 100,
    SWITCHING_PROTOCOLS             = 101,

    // 2xx Успешные
    OK                              = 200,
    CREATED                         = 201,
    ACCEPTED                        = 202,
    NO_CONTENT                      = 204,

    // 3xx Перенаправления
    MOVED_PERMANENTLY               = 301,
    FOUND                           = 302,
    SEE_OTHER                       = 303,
    NOT_MODIFIED                    = 304,
    TEMPORARY_REDIRECT              = 307,
    PERMANENT_REDIRECT              = 308,

    // 4xx Ошибки клиента
    BAD_REQUEST                     = 400,
    UNAUTHORIZED                    = 401,
    FORBIDDEN                       = 403,
    NOT_FOUND                       = 404,
    METHOD_NOT_ALLOWED              = 405,
    NOT_ACCEPTABLE                  = 406,
    REQUEST_TIMEOUT                 = 408,
    CONFLICT                        = 409,
    GONE                            = 410,
    PAYLOAD_TOO_LARGE               = 413,
    UNSUPPORTED_MEDIA_TYPE          = 415,
    TOO_MANY_REQUESTS               = 429,

    // 5xx Ошибки сервера
    INTERNAL_SERVER_ERROR           = 500,
    NOT_IMPLEMENTED                 = 501,
    BAD_GATEWAY                     = 502,
    SERVICE_UNAVAILABLE             = 503,
    GATEWAY_TIMEOUT                 = 504,
    HTTP_VERSION_NOT_SUPPORTED      = 505
};

/**
 * @struct HttpStatusUtil
 * @brief Утилитарная структура для конвертации и работы с перечислением HttpStatus.
 */
struct HttpStatusUtil
{
    /**
     * @brief Преобразует элемент HttpStatus в его официальное текстовое пояснение (Reason Phrase).
     * @param status Значение статус-кода из перечисления.
     * @return Строка с пояснением (например, "OK", "Not Found", "Internal Server Error").
     */
    static std::string ToString(HttpStatus status);

    /**
     * @brief Преобразует числовой код ответа в текстовое пояснение.
     * @param status Числовой идентификатор статус-кода (например, 200).
     * @return Строка с пояснением или "Unknown Status Code", если код неизвестен.
     */
    static std::string ToString(uint16_t status);

    /**
     * @brief Приводит значение перечисления HttpStatus к стандартному типу uint16_t.
     * @param status Значение статус-кода из перечисления.
     * @return Числовой код ответа (например, 404).
     */
    static uint16_t ToUInt16(HttpStatus status);

    /**
     * @brief Преобразует числовое значение в валидный элемент перечисления HttpStatus.
     * @param status Числовой идентификатор статус-кода.
     * @return Элемент HttpStatus. Если код неизвестен, возвращает HttpStatus::UNKNOWN.
     */
    static HttpStatus ToStatusClass(uint16_t status);
};

} // namespace http
} // namespace web

#endif // WEB_COMMON_LIB_HTTP_HTTP_STATUS_H_
