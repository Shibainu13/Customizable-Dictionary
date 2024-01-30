#ifndef INTENT_HPP
#define INTENT_HPP

#include <memory>
#include <map>
#include <string>
#include <stdexcept>

class Intent
{
public:
    typedef std::unique_ptr<Intent> Ptr;
    static const int NO_REQUEST_CODE = -1;
    static const int ACTION_NONE = -1;

private:
    class IntentExtra
    {
    public:
        virtual ~IntentExtra() = default;
    };

    template <typename T>
    class TypedIntentExtra : public IntentExtra
    {
    private:
        T value;

    public:
        TypedIntentExtra(T value);
        T getValue() const;
    };

    std::map<std::string, std::unique_ptr<IntentExtra>> extras;
    int requestCode;
    int action;

public:
    class Builder
    {
    private:
        std::unique_ptr<Intent> intent;

    public:
        Builder();
        Builder &setAction(int action);
        Builder &setRequestCode(int requestCode);

        template <typename T>
        Builder &putExtra(const std::string &key, T value);

        std::unique_ptr<Intent> build();
    };

    Intent();
    void setAction(int action);
    int getAction() const;
    void setRequestCode(int requestCode);
    int getRequestCode() const;

    template <typename T>
    void putExtra(const std::string &key, T value);
    bool hasExtra(const std::string &key);

    template <typename T>
    T getExtra(const std::string &key, T defaultValue);

    template <typename T>
    T getExtra(const std::string &key);
};

#include <Intent.inl>

#endif