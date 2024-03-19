#ifndef BUTTON_VIEW_HPP
#define BUTTON_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <ViewGroup.hpp>
#include <EventListener.hpp>
#include <RoundedRectangleShape.hpp>

#include <iostream>
#include <memory>

class ButtonView : public ViewGroup
{
public:
    typedef std::unique_ptr<ButtonView> Ptr;

public:
    enum ButtonShape
    {
        rect,
        rounded_rect,
        circle
    };
    const unsigned int DEFAULT_CORNER_POINT = 4;

private:
    sf::Shape *mShape;
    sf::Sprite mSprite;
    sf::Text mText;
    ButtonShape currentShape;

public:
    ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text);
    ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, const sf::Vector2f &position);
    ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size);
    ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);
    ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::IntRect &textureRect);
    ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::IntRect &textureRect, const sf::Vector2f &size);

    ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::IntRect &textureRect, const sf::Vector2f &size, const sf::Vector2f &spriteSize);

    ButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &size, const sf::Color &fillColor);
    ButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor);
    ButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor);

    ~ButtonView();

    void setTexture(const sf::Texture &texture, bool resetRect = false);
    void setTextureRect(const sf::IntRect &rect);
    void setText(const std::string &text);
    void setText(const std::string &text, const sf::Vector2f &relativePos);
    void setBackgroundColor(const sf::Color &color);
    void setTextColor(const sf::Color &color);
    bool isMouseHovering(const sf::Vector2f &mousePoint) const;
    void setCircleButton();
    void setBorderColor(const sf::Color &color, float thickness);
    void rescaleTexture(const sf::Vector2f &size);
    void centerSprite();

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;
    std::string getText() const;

    void setCornersRadius(float radius, unsigned int point);
    float getCornersRadius() const;
    unsigned int getCornerPoint() const;

protected:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual bool isOnMouseButtonPressed(const sf::Event &event) const override;
    virtual bool isOnMouseButtonReleased(const sf::Event &event) const override;
    virtual bool isOnMouseMoved(const sf::Event &event) const override;
};

#endif