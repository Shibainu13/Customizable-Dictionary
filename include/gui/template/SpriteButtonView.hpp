#ifndef SPRITE_BUTTON_VIEW_HPP
#define SPRITE_BUTTON_VIEW_HPP

#include <EventPublisher.hpp>
#include <ButtonView.hpp>

class SpriteButtonView : public ButtonView
{
public:
    typedef std::unique_ptr<SpriteButtonView> Ptr;

public:
    enum class ButtonType
    {
        NORMAL,
        HOVERING,
        PRESSED,
        COUNT
    };

private:
    static constexpr int BORDER_WIDTH = 2.f;

private:
    std::string mTexts[int(ButtonType::COUNT)];
    sf::IntRect mTextureRects[int(ButtonType::COUNT)];
    sf::Color mBorderColors[int(ButtonType::COUNT)];

public:
    SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string *texts, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);
    SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string *texts, unsigned int characterSize, const sf::Vector2f &position);

    SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, sf::Color *borderColors);

    SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);
    SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const char *text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);
    SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position);
    SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const char *text, unsigned int characterSize, const sf::Vector2f &position);

    void setOnMouseButtonPressed(EventCallback onMouseButtonPressed) override;
    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;
    void setOnMouseMoved(EventCallback onMouseMoved) override;
};

#endif