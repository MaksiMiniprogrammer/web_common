#pragma once

#ifndef WEB_COMMON_LIB_SESSION_SESSION_H_
#define WEB_COMMON_LIB_SESSION_SESSION_H_

#include <string>
#include <chrono>
#include <memory>

#include <web_common/session/user_role.h>

/**
 * @file session.h
 * @brief Определение класса Session и фабричных функций управления сессиями.
 */

namespace web
{
namespace session
{

/**
 * @class Session
 * @brief Класс, инкапсулирующий данные и логику жизненного цикла сессии пользователя.
 * 
 * Управляет идентификаторами, токенами безопасности (CSRF), ролями доступа
 * и гарантирует защиту от скачков системного времени (NTP) за счет гибридного 
 * использования system_clock и steady_clock.
 */
class Session
{
public:

    /**
     * @brief Время жизни сессии по умолчанию в секундах (30 минут).
     */
    static constexpr int DEFAULT_SESSION_TTL_SEC = 1800;

    /**
     * @brief Конструктор по умолчанию. Создает пустую (неинициализированную) сессию.
     * 
     * IsInit() для такого объекта вернет false, а IsExpired() всегда вернет true.
     */
    Session();

    /**
     * @brief Параметризованный конструктор для восстановления сессии из внешнего хранилища (БД/Redis).
     * @param sessionId Уникальный идентификатор сессии.
     * @param sessionTicket Секретный тикет сессии.
     * @param sessionTokenCSRF Токен защиты от CSRF-атак.
     * @param createdAt Календарная дата и время создания сессии.
     * @param expiryTime Календарная дата и время автоматического истечения сессии.
     * @param role Объект роли пользователя, привязанный к данной сессии.
     */
    Session(std::string sessionId, 
        std::string sessionTicket, 
        std::string sessionTokenCSRF, 
        std::chrono::system_clock::time_point createdAt,
        std::chrono::system_clock::time_point expiryTime,
        UserRole role);

    /**
     * @brief Деструктор по умолчанию.
     */
    ~Session() = default;

    // Запрет копирования сессии (сессия должна быть уникальной сущностью)
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    
    // Разрешение перемещения сессии для эффективной работы в контейнерах
    Session(Session&&) noexcept = default;
    Session& operator=(Session&&) noexcept = default;

    /**
     * @brief Получить идентификатор сессии.
     * @return Строка с ID сессии.
     */
    std::string GetSessionId() const;

    /**
     * @brief Установить новый идентификатор сессии.
     * @param sessionId Новый ID сессии.
     */
    void SetSessionId(const std::string& sessionId);

    /**
     * @brief Получить тикет сессии.
     * @return Строка с тикетом.
     */
    std::string GetSessionTicket() const;

    /**
     * @brief Установить тикет сессии.
     * @param sessionTicket Новый тикет.
     */
    void SetSessionTicket(const std::string& sessionTicket);

    /**
     * @brief Получить текущий CSRF-токен сессии.
     * @return Строка с токеном CSRF.
     */
    std::string GetSessionTokenCSRF() const;

    /**
     * @brief Установить новый CSRF-токен для защиты запросов.
     * @param sessionTokenCSRF Строка с новым CSRF-токеном.
     */
    void SetSessionTokenCSRF(const std::string& sessionTokenCSRF);

    /**
     * @brief Получить точное календарное время создания сессии.
     * @return Точка во времени system_clock.
     */
    std::chrono::system_clock::time_point GetCreatedAt() const;

    /**
     * @brief Получить монотонное время истечения сессии.
     * 
     * Используется для локальных и точных проверок таймаута внутри сервера.
     * @return Точка во времени steady_clock.
     */
    std::chrono::steady_clock::time_point GetExpiryTimeStamp() const;
    
    /**
     * @brief Получить календарное время истечения сессии.
     * 
     * Используется для сохранения актуального дедлайна обратно в БД или Redis.
     * @return Точка во времени system_clock.
     */
    std::chrono::system_clock::time_point GetExpirySystemTime() const;

    /**
     * @brief Получить текущий интервал времени жизни (TTL) сессии.
     * @return Длительность в формате steady_clock::duration.
     */
    std::chrono::steady_clock::duration GetTtl() const;

    /**
     * @brief Изменить время жизни (TTL) сессии.
     * 
     * Метод автоматически пересчитывает и сдвигает вперед календарную (system) 
     * и монотонную (steady) временные точки истечения сессии.
     * @param ttl Новая продолжительность жизни сессии.
     */
    void SetTtl(std::chrono::steady_clock::duration ttl);

    /**
     * @brief Получить объект роли пользователя, связанный с этой сессией.
     * @return Экземпляр UserRole.
     */
    UserRole GetRole() const;

    /**
     * @brief Назначить или изменить роль пользователя для текущей сессии.
     * @param role Новый объект роли UserRole.
     */
    void SetRole(UserRole role);

    /**
     * @brief Проверить, проинициализирована ли сессия.
     * @return true, если sessionId_ содержит непустую строку.
     */
    bool IsInit() const;

    /**
     * @brief Проверить, истекло ли время действия сессии.
     * 
     * Проверка выполняется по надежным монотонным часам. 
     * Неинициализированная сессия всегда считается истекшей.
     * @return true, если сессия протухла или не инициализирована.
     */
    bool IsExpired() const;

private:

    std::string sessionId_;            ///< Уникальный ID сессии (обычно UUID v4).
    std::string sessionTicket_;        ///< Защищенный авторизационный тикет.
    std::string sessionTokenCSRF_;     ///< Токен валидации межсайтовой подделки запросов.
    std::chrono::system_clock::time_point createdAt_;        ///< Календарная метка создания (неизменяемая).
    std::chrono::system_clock::time_point expirySystemTime_; ///< Календарный дедлайн для записи в БД.
    std::chrono::steady_clock::time_point expirySteadyTime_; ///< Внутренний монотонный дедлайн против сдвигов NTP.
    std::chrono::steady_clock::duration ttl_;                ///< Временной интервал валидности сессии.
    UserRole role_;                    ///< Роль текущего пользователя в рамках сессии.
};

/**
 * @brief Вспомогательная функция для генерации криптографически стойкого UUID сессии.
 * @return Случайная строка UUID v4.
 */
std::string MakeSessionId();

} // namespace session
} // namespace web

/**
 * @brief Умный указатель на объект сессии.
 */
using SessionPtr = std::shared_ptr<web::session::Session>;

/**
 * @brief Фабричная функция для создания новой валидной сессии.
 * 
 * Автоматически генерирует UUID сессии, проставляет текущие метки времени 
 * и задает роль UNKNOWN.
 * @param defaultTtl Время жизни новой сессии (по умолчанию берется Session::DEFAULT_SESSION_TTL_SEC).
 * @return Умный указатель на созданный объект Session.
 */
SessionPtr CreateSessionObject(std::chrono::steady_clock::duration defaultTtl = std::chrono::seconds(web::session::Session::DEFAULT_SESSION_TTL_SEC));

/**
 * @brief Фабричная функция для сборки (восстановления) сессии из базы данных.
 * 
 * Корректно рассчитывает внутреннее монотонное время на базе переданного 
 * календарного expiryTime, защищая инстанс от рассинхронизации часов.
 * @param id Прочитанный из БД ID сессии.
 * @param ticket Прочитанный из БД тикет сессии.
 * @param csrf Прочитанный из БД CSRF-токен.
 * @param createdAt Дата создания сессии из БД.
 * @param expiryTime Дата окончания сессии из БД.
 * @param role Роль пользователя, восстановленная из БД.
 * @return Умный указатель на восстановленный объект Session.
 */
SessionPtr CreateSessionObject(std::string id, 
    std::string ticket, 
    std::string csrf, 
    std::chrono::system_clock::time_point createdAt,
    std::chrono::system_clock::time_point expiryTime,
    web::session::UserRole role);

#endif // WEB_COMMON_LIB_SESSION_SESSION_H_