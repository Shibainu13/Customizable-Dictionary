#ifndef TEXT_BUTTON_VIEW_HPP
#define TEXT_BUTTON_VIEW_HPP

#include <ButtonView.hpp>
#include <Activity.hpp>
#include <EventListener.hpp>

class TextButtonView : public ButtonView
{
public:
    typedef std::unique_ptr<TextButtonView> Ptr;

public:
    enum class ButtonType
    {
        NORMAL,
        HOVERING,
        PRESSED,
        COUNT
    };

private:
    sf::Color textColors[3];

public:
    TextButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color *colors);

    void setOnMouseButtonPressed(EventCallback onMouseButtonPressed) override;
    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;
    void setOnMouseMoved(EventCallback onMouseMoved) override;
};

#endif