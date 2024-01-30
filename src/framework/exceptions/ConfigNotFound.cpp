#include <ConfigNotFound.hpp>

ConfigNotFound::ConfigNotFound(const ConfigKey key)
    : std::runtime_error("Config key not found " + std::to_string(static_cast<int>(key)))
{
}