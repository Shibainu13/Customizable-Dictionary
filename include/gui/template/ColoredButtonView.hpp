#ifndef COLORED_BUTTON_VIEW_HPP
#define COLORED_BUTTON_VIEW_HPP

#include <EventListener.hpp>
#include <Activity.hpp>
#include <ButtonView.hpp>

class ColoredButtonView : public ButtonView
{
public:
    typedef std::unique_ptr<ColoredButtonView> Ptr;

public:
    enum class ButtonType
    {
        NORMAL,
        HOVERING,
        PRESSED,
        COUNT
    };

private:
    sf::Color buttonColors[3];

public:
    ColoredButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color *colors);
    ColoredButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color *colors);

    void setOnMouseButtonPressed(EventCallback onMouseButtonPressed) override;
    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;
    void setOnMouseMoved(EventCallback onMouseMoved) override;
};

#endif