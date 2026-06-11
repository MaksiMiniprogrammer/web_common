#pragma once

#ifndef WEB_COMMON_LIB_UTILS_NETWORK_ENDPOINT_H_
#define WEB_COMMON_LIB_UTILS_NETWORK_ENDPOINT_H_

#include <string>
#include <cstdint>

/**
 * @file network_endpoint.h
 * @brief Определение структуры NetworkEndpoint для управления сетевыми адресами (IP и порт).
 */

namespace web
{
namespace utils
{

/**
 * @struct NetworkEndpoint
 * @brief Структура, представляющая сетевую точку подключения (IP-адрес и TCP/UDP порт).
 * 
 * Содержит методы для парсинга из строк, валидации IP-адресов и приведения 
 * адреса к стандартным текстовым форматам.
 */
struct NetworkEndpoint
{
    std::string ip;        ///< Строковое представление IP-адреса (например, "127.0.0.1" или "::1").
    uint16_t port = 0;     ///< Сетевой порт (0 - 65535).

    /**
     * @brief Конструктор по умолчанию. Создает неинициализированную точку (пустой IP, порт 0).
     */
    NetworkEndpoint() = default;

    /**
     * @brief Параметризованный конструктор.
     * @param ipAddress Строка с IP-адресом.
     * @param portNumber Номер сетевого порта.
     */
    NetworkEndpoint(std::string ipAddress, uint16_t portNumber);

    /**
     * @brief Проверяет, заполнены ли данные (был ли задан непустой IP).
     * @return true, если IP-адрес не пустой.
     */
    bool IsEmpty() const;

    /**
     * @brief Проверяет текущий IP-адрес на валидность (соответствие стандартам IPv4 или IPv6).
     * 
     * Использует механизмы Boost.Asio для строгой проверки синтаксиса.
     * @return true, если IP-адрес корректен.
     */
    bool IsValid() const;

    /**
     * @brief Проверяет, является ли текущий IP-адрес версией IPv4.
     * @return true, если адрес относится к семейству IPv4; false, если IPv6 или невалиден.
     */
    bool IsIPv4() const;

    /**
     * @brief Проверяет, является ли текущий IP-адрес версией IPv6.
     * @return true, если адрес относится к семейству IPv6; false, если IPv4 или невалиден.
     */
    bool IsIPv6() const;

    /**
     * @brief Приводит endpoint к классическому строковому виду "IP:PORT".
     * 
     * Для IPv6 автоматически добавляет квадратные скобки, например: "[::1]:8080".
     * @return Строка с полным сетевым адресом.
     */
    std::string ToString() const;

    /**
     * @brief Статический метод-парсер для сборки структуры из одной общей строки.
     * 
     * Корректно обрабатывает форматы "192.168.1.1:8080" и "[::1]:8080".
     * @param rawEndpoint Сырая строка сетевого адреса.
     * @return Сформированный объект NetworkEndpoint. Если порт не указан, он останется равным 0.
     */
    static NetworkEndpoint FromString(const std::string& rawEndpoint);
};

} // namespace utils
} // namespace web

#endif // WEB_COMMON_LIB_HTTP_NETWORK_ENDPOINT_H_
