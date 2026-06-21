#pragma once

#ifndef WEB_COMMON_LIB_HTTP_HTTP_URL_H_
#define WEB_COMMON_LIB_HTTP_HTTP_URL_H_

#include <string>
#include <unordered_map>

namespace web
{
namespace http
{

/**
 * @struct HttpUrl
 * @brief Структура для представления, парсинга и валидации компонентов URL.
 * 
 * Разбирает строки вида "/api/v1/user?id=42&sort=desc" на составные части:
 * путь, сырую query-строку и ассоциативную карту параметров.
 */
struct HttpUrl
{
    std::string path;         ///< URL-путь (например, "/api/v1/user")
    std::string rawQuery;     ///< Сырая query-строка после знака '?' (например, "id=42&sort=desc")
    
    // Карта распарсенных ключ-значение параметров
    std::unordered_map<std::string, std::string> queryParams;

    /**
     * @brief Конструктор по умолчанию. Создает пустой URL.
     */
    HttpUrl() = default;

    /**
     * @brief Конструктор с инициализацией базовых компонентов.
     */
    HttpUrl(std::string pathStr, std::string queryStr, std::unordered_map<std::string, std::string> params);

    /**
     * @brief Проверяет, пустой ли URL-адрес.
     */
    bool IsEmpty() const;

    /**
     * @brief Проверяет наличие конкретного query-параметра.
     * @param key Ключ параметра (например, "id").
     */
    bool HasParam(const std::string& key) const;

    /**
     * @brief Извлекает значение query-параметра.
     * @param key Ключ параметра.
     * @return Значение параметра или пустая строка, если ключ отсутствует.
     */
    std::string GetParam(const std::string& key) const;

    /**
     * @brief Статический метод-фабрика для сборки структуры из сырой строки.
     * @param rawUrl Сырая строка пути (например, "/search?q=text&page=2").
     * @return Сформированный объект HttpUrl.
     */
    static HttpUrl FromString(const std::string& rawUrl);
};

} // namespace http
} // namespace web

#endif // WEB_COMMON_LIB_HTTP_HTTP_URL_H_
