#include <WordButtonView.hpp>

WordButtonView::WordButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, ScrollRectView *sideView)
    : ButtonView(publisher, font, text, 22, position, sf::Vector2f(300, 50), sf::Color::White), sideView(sideView)
{
    buttonColors[0] = sf::Color::White;
    buttonColors[1] = sf::Color(255, 255, 255, 125);
    buttonColors[2] = sf::Color(255, 255, 255, 125);

    setBorderColor(sf::Color(0, 0, 0, 25), 1.f);
    setText(text, sf::Vector2f(8, 13));
    setTextColor(sf::Color::Black);

    setOnMouseButtonPressed([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseMoved([&](EventListener *listener, const sf::Event &event) {});
}

void WordButtonView::setOnMouseButtonPressed(EventCallback onMouseButtonPressed)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        this->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonPressed);
    EventListener::setOnMouseButtonPressed(onEvent);
}

void WordButtonView::setOnMouseButtonReleased(EventCallback onMouseButtonReleased)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        this->setBackgroundColor(buttonColors[(int)ButtonType::HOVERING]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonReleased);
    EventListener::setOnMouseButtonReleased(onEvent);
}

void WordButtonView::setOnMouseMoved(EventCallback onMouseMoved)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        WordButtonView *button = dynamic_cast<WordButtonView *>(listener);
        if (button->getGlobalBounds().contains(sideView->getRectMouseCoords()))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Right) ||
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

bool WordButtonView::isOnMouseButtonPressed(const sf::Event &event) const
{
    return this->getGlobalBounds().contains(sideView->getRectMouseCoords());
}

bool WordButtonView::isOnMouseButtonReleased(const sf::Event &event) const
{
    return this->getGlobalBounds().contains(sideView->getRectMouseCoords());
}

bool WordButtonView::isOnMouseMoved(const sf::Event &event) const
{
    return true;
}