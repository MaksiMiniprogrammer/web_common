#include <web_common/session/user_role.h>

namespace web
{
namespace session
{

std::string UserRoleUtil::ToString(UserRole role)
{
    switch (role)
    {
        case UserRole::USER:
            return "user";
        case UserRole::MODER:
            return "moder";
        case UserRole::ADMIN:
            return "admin";
        case UserRole::UNKNOWN:
        default:
            return "unknown";
    }
}

std::string UserRoleUtil::ToString(uint8_t role)
{
    return ToString(ToRoleClass(role));
}

UserRoleUtil::UserRole UserRoleUtil::FromString(const std::string& role)
{
    if (role == "user")  return UserRole::USER;
    if (role == "moder") return UserRole::MODER;
    if (role == "admin") return UserRole::ADMIN;
    return UserRole::UNKNOWN;
}

uint8_t UserRoleUtil::ToUInt8(UserRole role)
{
    return static_cast<uint8_t>(role);
}

UserRoleUtil::UserRole UserRoleUtil::ToRoleClass(uint8_t role)
{
    switch (role)
    {
        case static_cast<uint8_t>(UserRole::USER):
            return UserRole::USER;
        case static_cast<uint8_t>(UserRole::MODER):
            return UserRole::MODER;
        case static_cast<uint8_t>(UserRole::ADMIN):
            return UserRole::ADMIN;
        default:
            return UserRole::UNKNOWN;
    }
}

} // namespace session
} // namespace web
