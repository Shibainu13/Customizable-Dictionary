#include <AppConfig.hpp>

template <typename T>
inline AppConfig::TypedConfigValue<T>::TypedConfigValue(const T &value)
    : value(value)
{
}

template <typename T>
inline T AppConfig::TypedConfigValue<T>::getValue() const
{
    return value;
}

inline AppConfig::AppConfig()
{
    set(ConfigKey::APP_NAME, std::string("Earthium Dictionary"));
    set(ConfigKey::WINDOW_SIZE, sf::Vector2f(1280, 720));
    set(ConfigKey::FPS, int(60));
}

inline AppConfig &AppConfig::getInstance()
{
    static AppConfig appConfig;
    return appConfig;
}

inline AppConfig::~AppConfig()
{
    for (auto pair : mConfigMap)
        delete pair.second;
}

template <typename T>
inline T AppConfig::get(const ConfigKey key) const
{
    if (mConfigMap.count(key) > 0)
    {
        const ConfigValue *configValue = mConfigMap.at(key);
        if (const TypedConfigValue<T> *typedConfigValue = dynamic_cast<const TypedConfigValue<T> *>(configValue))
            return typedConfigValue->getValue();
    }
    throw ConfigNotFound(key);
}

template <typename T>
inline void AppConfig::set(const ConfigKey key, const T &value)
{
    mConfigMap[key] = new TypedConfigValue<T>(value);
}