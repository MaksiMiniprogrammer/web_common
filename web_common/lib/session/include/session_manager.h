#pragma once

#ifndef WEB_COMMON_LIB_SESSION_SESSION_MANAGER_H_
#define WEB_COMMON_LIB_SESSION_SESSION_MANAGER_H_

#include <functional>
#include <string>
#include <unordered_map>
#include <mutex>
#include <optional>

#include <web_common/session/session.h>
#include <web_common/utils/singleton.h>

/**
 * @file session_manager.h
 * @brief Определение класса SessionManager и связанных структур данных.
 */

namespace web
{
namespace session
{

/**
 * @brief Функция обратного вызова (каллбэк), активируемая при закрытии или уничтожении сессии.
 * @param sessionId Идентификатор сессии, которая была удалена.
 */
using SessionCallback = std::function<void(const std::string&)>;

/**
 * @struct SessionInfo
 * @brief Безопасный срез данных сессии (DTO) для предоставления информации внешним модулям.
 * 
 * Все поля являются копиями данных реального объекта, что защищает состояние 
 * сессии в менеджере от случайной модификации извне (Read-Only доступ).
 */
struct SessionInfo
{
    std::string sessionId;       ///< Уникальный идентификатор сессии.
    std::string sessionTicket;   ///< Авторизационный зашифрованный тикет пользователя.
    std::string sessionTokenCSRF;///< Токен валидации межсайтовой подделки запросов.
    UserRole role;               ///< Объект роли, ассоциированный с сессией.
    std::chrono::system_clock::time_point createdAt;  ///< Время создания сессии (календарное).
    std::chrono::system_clock::time_point expiryTime; ///< Время автоматического истечения сессии (календарное).
    bool isExpired;              ///< Флаг, указывающий, истек ли срок действия сессии.
};

/**
 * @class SessionManager
 * @brief Центральный потокобезопасный менеджер для управления жизненным циклом сессий пользователей.
 * 
 * Реализован как синглтон Майерса на базе паттерна CRTP (шаблон utils::Singleton).
 * Отвечает за создание, ротацию токенов безопасности, ручную и автоматическую очистку сессий в памяти.
 */
class SessionManager : public utils::Singleton<SessionManager>
{
private:
    // Предоставляем доступ базовому шаблону синглтона к приватному конструктору
    friend class utils::Singleton<SessionManager>;

    SessionManager() = default;
    ~SessionManager() = default;

public:

    /**
     * @brief Создает новую сессию с правами Администратора (ADMIN).
     * @param callback Кастомное действие при уничтожении сессии (опционально).
     * @return Строка с уникальным SessionId. В случае внутренней ошибки — пустая строка.
     */
    std::string CreateAdminSession(SessionCallback callback = nullptr);

    /**
     * @brief Создает новую сессию с правами Модератора (MODER).
     * @param callback Кастомное действие при уничтожении сессии (опционально).
     * @return Строка с уникальным SessionId. В случае внутренней ошибки — пустая строка.
     */
    std::string CreateModerSession(SessionCallback callback = nullptr);

    /**
     * @brief Создает новую сессию с правами обычного Пользователя (USER).
     * @param callback Кастомное действие при уничтожении сессии (опционально).
     * @return Строка с уникальным SessionId. В случае внутренней ошибки — пустая строка.
     */
    std::string CreateUserSession(SessionCallback callback = nullptr);

    /**
     * @brief Безопасно извлекает информацию о сессии без передачи прямого доступа к объекту.
     * @param sessionId Идентификатор запрашиваемой сессии.
     * @return std::optional с копией данных SessionInfo. Если сессия не найдена, возвращает std::nullopt.
     */
    std::optional<SessionInfo> GetSessionInfo(const std::string& sessionId);

    /**
     * @brief Продлевает время активности сессии на её исходный интервал TTL (Sliding Timeout).
     * @param sessionId Идентификатор продлеваемой сессии.
     * @return true, если сессия успешно найдена и продлена; false, если сессия отсутствует или уже мертва.
     */
    bool RefreshSession(const std::string& sessionId);

    /**
     * @brief Метод автоматической очистки памяти от протухших сессий.
     * 
     * Рекомендуется к вызову по периодическому таймеру. Находит все сессии с истекшим временем жизни, 
     * удаляет их из внутренних таблиц и безопасно выполняет связанные каллбэки вне критической секции.
     */
    void CleanExpiredSessions();

    /**
     * @brief Обновляет авторизационные и защитные токены в сессии (авторизация/ротация).
     * @param sessionId Идентификатор сессии.
     * @param ticket Новый авторизационный тикет.
     * @param csrfToken Новый защитный CSRF-токен.
     * @return true в случае успешного обновления; false, если сессия не найдена или истекла.
     */
    bool UpdateSessionSecurity(const std::string& sessionId, const std::string& ticket, const std::string& csrfToken);

    /**
     * @brief Выполняет валидацию присланного CSRF-токена на соответствие токену внутри сессии.
     * @param sessionId Идентификатор проверяемой сессии.
     * @param csrfToken Токен, полученный из HTTP-запроса клиента.
     * @return true, если токены не пусты и строго совпадают; false, если проверка провалена или сессия мертва.
     */
    bool ValidateCsrfToken(const std::string& sessionId, const std::string& csrfToken);

    /**
     * @brief Закрывает и удаляет конкретную сессию пользователя (Logout).
     * 
     * Метод немедленно высвобождает память сессии и активирует связанный SessionCallback.
     * @param sessionId Идентификатор удаляемой сессии.
     * @return true, если сессия существовала и была удалена; false, если сессия не найдена.
     */
    bool CloseSession(const std::string& sessionId);

    /**
     * @brief Принудительно завершает абсолютно все активные сессии в системе.
     * 
     * Используется при остановке сервера или сбросе авторизации. 
     * Последовательно выполняет каллбэки для всех удаляемых идентификаторов.
     */
    void CloseAllSessions();

private:

    /**
     * @brief Единый внутренний метод инициализации и регистрации сессий.
     * @param role Сформированный объект роли для новой сессии.
     * @param callback Каллбэк закрытия сессии.
     * @return Строка с сгенерированным SessionId.
     */
    std::string CreateSession(UserRole role, SessionCallback callback = nullptr);

    /**
     * @brief Находит внутренний объект сессии по его идентификатору.
     * 
     * Внимание: должен вызываться строго под защитой mutex_.
     * @param sessionId Идентификатор сессии.
     * @return Умный указатель SessionPtr или nullptr, если сессия не найдена.
     */
    SessionPtr GetSessionById(const std::string& sessionId) const;

    std::unordered_map<std::string, SessionPtr> sessions_;               ///< Таблица соответствия ID и объектов сессий.
    std::unordered_map<std::string, SessionCallback> sessionsCallbacks_; ///< Таблица зарегистрированных каллбэков удаления.

    mutable std::mutex mutex_; ///< Мьютекс для синхронизации доступа к хранилищам из параллельных потоков.
};

} // namespace session
} // namespace web

#endif // WEB_COMMON_LIB_SESSION_SESSION_MANAGER_H_
