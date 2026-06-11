#include <web_common/session/session_manager.h>

namespace web
{
namespace session
{

std::optional<SessionInfo> SessionManager::GetSessionInfo(const std::string& sessionId)
{
    SessionPtr session = GetSessionById(sessionId);
    
    if (!session || !session->IsInit())
    {
        return std::nullopt;
    }

    SessionInfo info;
    info.sessionId = session->GetSessionId();
    info.sessionTicket = session->GetSessionTicket();
    info.sessionTokenCSRF = session->GetSessionTokenCSRF();
    info.role = session->GetRole();
    info.createdAt = session->GetCreatedAt();
    info.expiryTime = session->GetExpirySystemTime();
    info.isExpired = session->IsExpired();

    return info;
}

std::string SessionManager::CreateAdminSession(SessionCallback callback)
{
    return CreateSession(UserRoleUtil::UserRole::ADMIN, callback);
}

std::string SessionManager::CreateModerSession(SessionCallback callback)
{
    return CreateSession(UserRoleUtil::UserRole::MODER, callback);
}

std::string SessionManager::CreateUserSession(SessionCallback callback)
{
    return CreateSession(UserRoleUtil::UserRole::USER, callback);
}

bool SessionManager::CloseSession(const std::string& sessionId)
{
    SessionCallback callback = nullptr;
    bool found = false;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto sessionIt = sessions_.find(sessionId);
        if (sessionIt != sessions_.end())
        {
            sessions_.erase(sessionIt);
            found = true;
        }

        auto callbackIt = sessionsCallbacks_.find(sessionId);
        if (callbackIt != sessionsCallbacks_.end())
        {
            callback = std::move(callbackIt->second);
            sessionsCallbacks_.erase(callbackIt);
        }
    }

    if (found && callback)
    {
        callback(sessionId);
    }

    return found;
}

void SessionManager::CloseAllSessions()
{
    std::vector<std::pair<std::string, SessionCallback>> sessionsToClose;

    {
        std::lock_guard<std::mutex> lock(mutex_);

        for (auto& [id, sessionPtr] : sessions_)
        {
            SessionCallback cb = nullptr;
            
            auto cbIt = sessionsCallbacks_.find(id);
            if (cbIt != sessionsCallbacks_.end())
            {
                cb = std::move(cbIt->second);
            }
            
            sessionsToClose.emplace_back(id, std::move(cb));
        }

        sessions_.clear();
        sessionsCallbacks_.clear();
    }

    for (const auto& [id, callback] : sessionsToClose)
    {
        if (callback != nullptr)
        {
            callback(id);
        }
    }
}

std::string SessionManager::CreateSession(UserRoleUtil::UserRole role, SessionCallback callback)
{
    SessionPtr newSession = CreateSessionObject();
    
    if (!newSession)
    {
        return std::string();
    }
    newSession->SetRole(role);

    std::lock_guard<std::mutex> lock(mutex_);
    
    std::string sessionId = newSession->GetSessionId();

    sessions_[sessionId] = newSession;

    if (callback != nullptr)
    {
        sessionsCallbacks_[sessionId] = std::move(callback);
    }

    return sessionId;
}

SessionPtr SessionManager::GetSessionById(const std::string& sessionId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = sessions_.find(sessionId);
    if (it != sessions_.end())
    {
        return it->second;
    }
    return nullptr;
}

bool SessionManager::RefreshSession(const std::string& sessionId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    
    SessionPtr session = GetSessionById(sessionId);
    if (!session || !session->IsInit() || session->IsExpired())
    {
        return false;
    }

    session->SetTtl(session->GetTtl());
    return true;
}

void SessionManager::CleanExpiredSessions()
{
    std::vector<std::pair<std::string, SessionCallback>> callbacksToExecute;

    {
        std::lock_guard<std::mutex> lock(mutex_);

        for (auto it = sessions_.begin(); it != sessions_.end(); )
        {
            if (it->second && it->second->IsExpired())
            {
                std::string id = it->first;

                auto cbIt = sessionsCallbacks_.find(id);
                if (cbIt != sessionsCallbacks_.end())
                {
                    if (cbIt->second != nullptr)
                    {
                        callbacksToExecute.emplace_back(id, std::move(cbIt->second));
                    }
                    sessionsCallbacks_.erase(cbIt); // Стираем колбэк из таблицы
                }

                it = sessions_.erase(it);
            }
            else
            {
                ++it; 
            }
        }
    } 

    for (const auto& [id, callback] : callbacksToExecute)
    {
        callback(id);
    }
}

bool SessionManager::UpdateSessionSecurity(const std::string& sessionId, const std::string& ticket, const std::string& csrfToken)
{
    std::lock_guard<std::mutex> lock(mutex_);

    SessionPtr session = GetSessionById(sessionId);
    if (!session || !session->IsInit() || session->IsExpired())
    {
        return false;
    }

    session->SetSessionTicket(ticket);
    session->SetSessionTokenCSRF(csrfToken);
    return true;
}

bool SessionManager::ValidateCsrfToken(const std::string& sessionId, const std::string& csrfToken)
{
    std::lock_guard<std::mutex> lock(mutex_);

    SessionPtr session = GetSessionById(sessionId);
    if (!session || !session->IsInit() || session->IsExpired())
    {
        return false;
    }

    const std::string& storedCsrf = session->GetSessionTokenCSRF();
    if (storedCsrf.empty() || csrfToken.empty())
    {
        return false;
    }

    return storedCsrf == csrfToken;
}
}
}