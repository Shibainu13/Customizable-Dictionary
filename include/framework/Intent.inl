#include <Intent.hpp>

template <typename T>
inline Intent::TypedIntentExtra<T>::TypedIntentExtra(T value)
    : value(value)
{
}

template <typename T>
inline T Intent::TypedIntentExtra<T>::getValue() const
{
    return value;
}

inline Intent::Builder::Builder()
{
    intent = std::make_unique<Intent>();
}

inline Intent::Builder &Intent::Builder::setAction(int action)
{
    if (action < 0)
        throw std::runtime_error("Action must be a non-negative integer");

    intent->setAction(action);
    return *this;
}

inline Intent::Builder &Intent::Builder::setRequestCode(int requestCode)
{
    if (requestCode < 0)
        throw std::runtime_error("Request code must be a non-negative integer");

    intent->setRequestCode(requestCode);
    return *this;
}

template <typename T>
inline Intent::Builder &Intent::Builder::putExtra(const std::string &key, T value)
{
    intent->putExtra(key, value);
    return *this;
}

inline std::unique_ptr<Intent> Intent::Builder::build()
{
    return std::move(intent);
}

inline Intent::Intent()
    : requestCode(NO_REQUEST_CODE)
{
}

inline void Intent::setAction(int action)
{
    if (action < 0)
        throw std::runtime_error("Action must be a non-negative integer");

    this->action = action;
}

inline int Intent::getAction() const
{
    return action;
}

inline void Intent::setRequestCode(int requestCode)
{
    if (requestCode < 0)
        throw std::runtime_error("Request code must be a non-negative integer");

    this->requestCode = requestCode;
}

inline int Intent::getRequestCode() const
{
    return requestCode;
}

template <typename T>
inline void Intent::putExtra(const std::string &key, T value)
{
    extras[key] = std::make_unique<TypedIntentExtra<T>>(value);
}

inline bool Intent::hasExtra(const std::string &key)
{
    return extras.find(key) != extras.end();
}

template <typename T>
inline T Intent::getExtra(const std::string &key, T defaultValue)
{
    if (hasExtra(key))
        return getExtra<T>(key);
    else
        return defaultValue;
}

template <typename T>
inline T Intent::getExtra(const std::string &key)
{
    if (hasExtra(key))
        return static_cast<TypedIntentExtra<T> *>(extras[key].get())->getValue();
    else
        throw std::runtime_error("No extra with key " + key);
}