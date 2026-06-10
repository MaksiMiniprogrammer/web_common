#pragma once

#ifndef WEB_COMMON_LIB_SESSION_USER_ROLE_H_
#define WEB_COMMON_LIB_SESSION_USER_ROLE_H_

#include <cstdint>
#include <string>

/**
 * @file user_role.h
 * @brief Определение ролей пользователей и функций для их конвертации.
 */

namespace web
{
namespace session
{

/**
 * @enum UserRole
 * @brief Перечисление доступных ролей пользователей.
 */
enum class UserRole : uint8_t
{
    UNKNOWN         = 0, ///< Неизвестная или неинициализированная роль.
    USER            = 1, ///< Обычный пользователь.
    MODER           = 2, ///< Модератор с расширенными правами.
    ADMIN           = 3  ///< Администратор с полным доступом.
};

/**
 * @brief Преобразует значение перечисления Role в строковое представление.
 * @param role Значение роли из перечисления.
 * @return Строка (например, "admin", "moder", "user", "unknown").
 */
static std::string ToString(UserRole role);

/**
 * @brief Преобразует числовое значение роли в строковое представление.
 * @param role Числовой идентификатор роли.
 * @return Строка с названием роли или "unknown", если ID невалиден.
 */
static std::string ToString(uint8_t role);

/**
 * @brief Создает значение перечисления Role из строки.
 * @param role Строковое имя роли (регистрозависимое).
 * @return Соответствующий элемент Role. Если строка не совпадает, возвращает Role::UNKNOWN.
 */
static UserRole FromString(const std::string& role);

/**
 * @brief Приводит значение перечисления Role к типу uint8_t.
 * @param role Значение роли из перечисления.
 * @return Числовой идентификатор роли.
 */
static uint8_t ToUInt8(UserRole role);

/**
 * @brief Преобразует числовое значение в валидный элемент перечисления Role.
 * @param role Числовой идентификатор роли.
 * @return Элемент Role. Если ID неизвестен, возвращает Role::UNKNOWN.
 */
static UserRole ToRoleClass(uint8_t role);

} // namespace session
} // namespace web

#endif // WEB_COMMON_LIB_SESSION_USER_ROLE_H_
