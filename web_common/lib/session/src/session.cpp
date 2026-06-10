#include <web_common/session/session.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace web
{
namespace session
{

Session::Session()
: sessionId_()
, createdAt_(std::chrono::system_clock::time_point{})
, expirySystemTime_(std::chrono::system_clock::time_point{})
, expirySteadyTime_(std::chrono::steady_clock::time_point{})
, ttl_(std::chrono::seconds(0))
, role_(UserRole::UNKNOWN)
{
}

Session::Session(std::string sessionId, 
    std::string sessionTicket, 
    std::string sessionTokenCSRF, 
    std::chrono::system_clock::time_point createdAt,
    std::chrono::system_clock::time_point expiryTime,
    UserRole role)
: sessionId_(std::move(sessionId))
, sessionTicket_(std::move(sessionTicket))
, sessionTokenCSRF_(std::move(sessionTokenCSRF))
, createdAt_(createdAt)
, expirySystemTime_(expiryTime)
, role_(role)
{
    auto nowSys = std::chrono::system_clock::now();
    auto nowSteady = std::chrono::steady_clock::now();

    if (expiryTime <= nowSys) 
    {
        expirySteadyTime_ = nowSteady - std::chrono::seconds(1);
        ttl_ = std::chrono::seconds(0);
    } 
    else 
    {
        auto remaining = expiryTime - nowSys;
        
        expirySteadyTime_ = nowSteady + std::chrono::duration_cast<std::chrono::steady_clock::duration>(remaining);
        ttl_ = std::chrono::duration_cast<std::chrono::steady_clock::duration>(remaining);
    }
}

std::string Session::GetSessionId() const
{
    return sessionId_;
}

void Session::SetSessionId(const std::string& sessionId)
{
    sessionId_ = sessionId;
}

std::string Session::GetSessionTicket() const
{
    return sessionTicket_;
}

void Session::SetSessionTicket(const std::string& sessionTicket)
{
    sessionTicket_ = sessionTicket;
}

std::string Session::GetSessionTokenCSRF() const
{
    return sessionTokenCSRF_;
}

void Session::SetSessionTokenCSRF(const std::string& sessionTokenCSRF)
{
    sessionTokenCSRF_ = sessionTokenCSRF;
}

std::chrono::system_clock::time_point Session::GetCreatedAt() const 
{ 
    return createdAt_; 
}

std::chrono::system_clock::time_point Session::GetExpirySystemTime() const 
{ 
    return expirySystemTime_; 
}

std::chrono::steady_clock::duration Session::GetTtl() const 
{ 
    return ttl_; 
}

void Session::SetTtl(std::chrono::steady_clock::duration ttl) 
{ 
    if (!IsInit()) return;
    
    ttl_ = ttl;
    expirySteadyTime_ = std::chrono::steady_clock::now() + ttl;
    expirySystemTime_ = std::chrono::system_clock::now() + std::chrono::duration_cast<std::chrono::system_clock::duration>(ttl);
}

std::chrono::steady_clock::time_point Session::GetExpiryTimeStamp() const
{
    return expirySteadyTime_;
}

UserRole Session::GetRole() const
{
    return role_;
}

void Session::SetRole(UserRole role)
{
    role_ = role;
}

std::string MakeSessionId()
{
    return boost::uuids::to_string(boost::uuids::random_generator()());
}

bool Session::IsInit() const
{
    return !sessionId_.empty();
}

bool Session::IsExpired() const
{
    if (!IsInit()) 
    {
        return true; 
    }
    return std::chrono::steady_clock::now() >= expirySteadyTime_;
}

} // namespace session
} // namespace web

SessionPtr CreateSessionObject(std::chrono::steady_clock::duration defaultTtl)
{
    auto nowSys = std::chrono::system_clock::now();
    auto expirySys = nowSys + std::chrono::duration_cast<std::chrono::system_clock::duration>(defaultTtl);
    
    return std::make_shared<web::session::Session>(
        web::session::MakeSessionId(), "", "", nowSys, expirySys, web::session::UserRole::UNKNOWN
    );
}

SessionPtr CreateSessionObject(std::string id, 
    std::string ticket, 
    std::string csrf, 
    std::chrono::system_clock::time_point createdAt,
    std::chrono::system_clock::time_point expiryTime,
    web::session::UserRole role) 
{
    return std::make_shared<web::session::Session>(
        std::move(id), std::move(ticket), std::move(csrf), createdAt, expiryTime, role
    );
}