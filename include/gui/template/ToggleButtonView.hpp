#ifndef TOGGLE_BUTTON_VIEW_HPP
#define TOGGLE_BUTTON_VIEW_HPP

#include <EventPublisher.hpp>
#include <ButtonView.hpp>

class ToggleButtonView : public ButtonView
{
public:
    typedef std::unique_ptr<ToggleButtonView> Ptr;

public:
    enum class ButtonType
    {
        OFF,
        ON,
        COUNT
    };

    static constexpr int DEFAULT_BORDER_WIDTH = 2.f;

private:
    std::string mTexts[(int)ButtonType::COUNT];
    sf::IntRect mTextureRects[(int)ButtonType::COUNT];
    sf::Color mBorderColors[(int)ButtonType::COUNT];
    bool mIsOn = false;

public:
    // @Params 0: OFF, 1: ON
    ToggleButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string *texts, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);
    ToggleButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string *texts, unsigned int characterSize, const sf::Vector2f &position);

    ToggleButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Vector2f &spriteSize);
    ToggleButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Vector2f &spriteSize, const sf::Color *borderColors);

    ToggleButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);
    ToggleButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const char *text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);
    ToggleButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position);
    ToggleButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const char *text, unsigned int characterSize, const sf::Vector2f &position);

    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;

    void setState(bool isOn);
    void toggleState();
    bool getState() const;
};

#endif