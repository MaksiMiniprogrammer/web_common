#pragma once

#ifndef WEB_COMMON_LIB_HTTP_HTTP_METHOD_H_
#define WEB_COMMON_LIB_HTTP_HTTP_METHOD_H_

#include <cstdint>
#include <string>

/**
 * @file http_method.h
 * @brief Определение HTTP-методов и функций для их конвертации.
 */

namespace web
{
namespace http
{

/**
 * @struct HttpMethodUtil
 * @brief Структура для управления HTTP-методами.
 * 
 * Содержит перечисление HttpMethod и статические утилитарные методы 
 * для преобразования между типами HttpMethod, uint8_t и std::string.
 */
struct HttpMethodUtil
{
    /**
     * @enum HttpMethod
     * @brief Перечисление поддерживаемых HTTP-методов.
     */
    enum class HttpMethod : uint8_t
    {
        UNKNOWN = 0, ///< Неизвестный или неподдерживаемый метод.
        GET     = 1, ///< Метод запроса данных GET.
        PUT     = 2, ///< Метод обновления данных PUT.
        POST    = 3, ///< Метод отправки данных POST.
        DELETE  = 4  ///< Метод удаления данных DELETE.
    };

    /**
     * @brief Преобразует значение перечисления HttpMethod в строковое представление.
     * @param method Значение метода из перечисления.
     * @return Строка в верхнем регистре (например, "GET", "POST", "UNKNOWN").
     */
    static std::string ToString( HttpMethod method );

    /**
     * @brief Преобразует числовое значение HTTP-метода в строковое представление.
     * @param method Числовой идентификатор метода.
     * @return Строка с названием метода или "UNKNOWN", если ID невалиден.
     */
    static std::string ToString( uint8_t method );

    /**
     * @brief Создает значение перечисления HttpMethod из строки.
     * @param method Строковое имя метода (регистрозависимое, ожидает верхний регистр).
     * @return Соответствующий элемент HttpMethod. Если строка не совпадает, возвращает HttpMethod::UNKNOWN.
     */
    static HttpMethod FromString( const std::string& method );

    /**
     * @brief Приводит значение перечисления HttpMethod к типу uint8_t.
     * @param method Значение метода из перечисления.
     * @return Числовой идентификатор метода.
     */
    static uint8_t ToUInt8( HttpMethod method );

    /**
     * @brief Преобразует числовое значение в валидный элемент перечисления HttpMethod.
     * @param method Числовой идентификатор метода.
     * @return Элемент HttpMethod. Если ID неизвестен, возвращает HttpMethod::UNKNOWN.
     */
    static HttpMethod ToMethodClass( uint8_t method );
};

} // namespace http
} // namespace web

#endif // WEB_COMMON_LIB_HTTP_HTTP_METHOD_H_
