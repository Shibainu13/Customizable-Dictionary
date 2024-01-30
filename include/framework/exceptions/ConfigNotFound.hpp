#ifndef CONFIG_NOT_FOUND_HPP
#define CONFIG_NOT_FOUND_HPP

#include <AppConfigKey.hpp>
#include <stdexcept>
#include <iostream>

class ConfigNotFound : public std::runtime_error
{
public:
    ConfigNotFound(const ConfigKey key);
};

#endif