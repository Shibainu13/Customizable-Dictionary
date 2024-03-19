#include <TextButtonView.hpp>

TextButtonView::TextButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color *colors)
    : ButtonView(publisher, font, text, characterSize, position, size, sf::Color::Transparent)
{
    for (int i = 0; i < (int)ButtonType::COUNT; i++)
        textColors[i] = colors[i];

    setOnMouseButtonPressed([&](EventListener* listener, const sf::Event& event) {});
    setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {});
    setOnMouseMoved([&](EventListener* listener, const sf::Event& event) {});
}

void TextButtonView::setOnMouseButtonPressed(EventCallback onMouseButtonPressed)
{
    EventListener::EventDoubleCallback onDoubleCallback = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        this->setTextColor(textColors[(int)ButtonType::PRESSED]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleCallback, std::placeholders::_1, std::placeholders::_2, onMouseButtonPressed);
    EventListener::setOnMouseButtonPressed(onEvent);
}

void TextButtonView::setOnMouseButtonReleased(EventCallback onMouseButtonReleased)
{
    EventListener::EventDoubleCallback onDoubleCallback = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        this->setTextColor(textColors[(int)ButtonType::HOVERING]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleCallback, std::placeholders::_1, std::placeholders::_2, onMouseButtonReleased);
    EventListener::setOnMouseButtonReleased(onEvent);
}

void TextButtonView::setOnMouseMoved(EventCallback onMouseMoved)
{
    EventListener::EventDoubleCallback onDoubleCallback = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        if (this->isMouseHovering(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Right)||
                sf::Mouse::isButtonPressed(sf::Mouse::Middle))
                this->setTextColor(textColors[(int)ButtonType::PRESSED]);
            else
                this->setTextColor(textColors[(int)ButtonType::HOVERING]);
        }
        else 
            this->setTextColor(textColors[(int)ButtonType::NORMAL]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleCallback, std::placeholders::_1, std::placeholders::_2, onMouseMoved);
    EventListener::setOnMouseMoved(onEvent);
}