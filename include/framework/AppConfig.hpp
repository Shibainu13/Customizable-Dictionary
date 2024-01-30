#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include <SFML/Graphics.hpp>

#include <AppConfigKey.hpp>
#include <ConfigNotFound.hpp>

#include <unordered_map>
#include <stdexcept>
#include <string>
#include <utility>

class AppConfig
{
private:
    class ConfigValue
    {
    public:
        virtual ~ConfigValue() = default;
    };

    template <typename T>
    class TypedConfigValue : public ConfigValue
    {
    public:
        TypedConfigValue(const T &value);
        T getValue() const;

    private:
        T value;
    };

private:
    AppConfig();
    std::unordered_map<ConfigKey, ConfigValue *> mConfigMap;

public:
    AppConfig(const AppConfig &) = delete;
    AppConfig &operator=(const AppConfig &) = delete;
    ~AppConfig();

    static AppConfig &getInstance();

    template <typename T>
    T get(const ConfigKey key) const;

    template <typename T>
    void set(const ConfigKey key, const T &value);
};

#include <AppConfig.inl>

#endif