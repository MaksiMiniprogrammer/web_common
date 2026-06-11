#pragma once

#ifndef WEB_COMMON_LIB_HTTP_HTTP_VERSION_H_
#define WEB_COMMON_LIB_HTTP_HTTP_VERSION_H_

#include <cstdint>
#include <string>

/**
 * @file http_version.h
 * @brief Определение версий HTTP-протокола и функций для их конвертации.
 */

namespace web
{
namespace http
{

/**
 * @struct HttpVersionUtil
 * @brief Структура для управления версиями HTTP.
 * 
 * Содержит перечисление HttpVersion и статические утилитарные методы 
 * для преобразования между типами HttpVersion, uint8_t и std::string.
 */
struct HttpVersionUtil
{
    /**
     * @enum HttpVersion
     * @brief Перечисление поддерживаемых и исторических версий HTTP.
     */
    enum class HttpVersion : uint8_t
    {
        UNKNOWN  = 0, ///< Неизвестная или неподдерживаемая версия.
        HTTP_0_9 = 1, ///< Исторический HTTP/0.9.
        HTTP_1_0 = 2, ///< Текстовый протокол HTTP/1.0.
        HTTP_1_1 = 3, ///< Классический широко используемый HTTP/1.1.
        HTTP_2_0 = 4, ///< Бинарный мультиплексированный HTTP/2.
        HTTP_3_0 = 5  ///< Современный HTTP/3 поверх QUIC (UDP).
    };

    /**
     * @brief Преобразует значение перечисления HttpVersion в строковое представление.
     * @param version Значение версии из перечисления.
     * @return Строка стандарта (например, "HTTP/1.1", "HTTP/2", "UNKNOWN").
     */
    static std::string ToString( HttpVersion version );

    /**
     * @brief Преобразует числовое значение версии HTTP в строковое представление.
     * @param version Числовой идентификатор версии.
     * @return Строка с названием версии или "UNKNOWN", если ID невалиден.
     */
    static std::string ToString( uint8_t version );

    /**
     * @brief Создает значение перечисления HttpVersion из строки.
     * @param version Строковое имя версии (ожидает верхний регистр, например "HTTP/1.1").
     * @return Соответствующий элемент HttpVersion. В случае несовпадения возвращает HttpVersion::UNKNOWN.
     */
    static HttpVersion FromString( const std::string& version );

    /**
     * @brief Приводит значение перечисления HttpVersion к типу uint8_t.
     * @param version Значение версии из перечисления.
     * @return Числовой идентификатор версии.
     */
    static uint8_t ToUInt8( HttpVersion version );

    /**
     * @brief Преобразует числовое значение в валидный элемент перечисления HttpVersion.
     * @param version Числовой идентификатор версии.
     * @return Элемент HttpVersion. Если ID неизвестен, возвращает HttpVersion::UNKNOWN.
     */
    static HttpVersion ToVersionClass( uint8_t version );
};

} // namespace http
} // namespace web

#endif // WEB_COMMON_LIB_HTTP_HTTP_VERSION_H_
