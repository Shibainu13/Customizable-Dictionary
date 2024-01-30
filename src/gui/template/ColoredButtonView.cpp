#include <ColoredButtonView.hpp>

ColoredButtonView::ColoredButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color *colors)
    : ColoredButtonView(publisher, font, text, 30, position, size, colors)
{
}

ColoredButtonView::ColoredButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color *colors)
    : ButtonView(publisher, font, text, characterSize, position, size, colors[0])
{
    for (int i = 0; i < (int)ButtonType::COUNT; i++)
        buttonColors[i] = colors[i];

    setOnMouseButtonPressed([&](EventListener* listener, const sf::Event& event) {});
    setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {});
    setOnMouseMoved([&](EventListener* listener, const sf::Event& event) {});
}

void ColoredButtonView::setOnMouseButtonPressed(EventCallback onMouseButtonPressed)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener* listener, const sf::Event& event, EventCallback callback)
    {
        this->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonPressed);
    EventListener::setOnMouseButtonPressed(onEvent);
}

void ColoredButtonView::setOnMouseButtonReleased(EventCallback onMouseButtonReleased)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener* listener, const sf::Event& event, EventCallback callback)
    {
        this->setBackgroundColor(buttonColors[(int)ButtonType::HOVERING]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonReleased);
    EventListener::setOnMouseButtonReleased(onEvent);
}

void ColoredButtonView::setOnMouseMoved(EventCallback onMouseMoved)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener* listener, const sf::Event& event, EventCallback callback)
    {
        if (this->isMouseHovering(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Right)||
                sf::Mouse::isButtonPressed(sf::Mouse::Middle))
                this->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
            else
                this->setBackgroundColor(buttonColors[(int)ButtonType::HOVERING]);
        }
        else
            this->setBackgroundColor(buttonColors[(int)ButtonType::NORMAL]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseMoved);
    EventListener::setOnMouseMoved(onEvent);
}