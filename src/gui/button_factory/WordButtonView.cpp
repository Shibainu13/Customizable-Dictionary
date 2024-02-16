#include <WordButtonView.hpp>

// ButtonView::Ptr WordButtonFactory::create(Activity *context, const sf::Font &font, const std::string &text, const sf::Vector2f &position, SideBackgroundView* sideView, EventListener::EventCallback callback)
// {
//     sf::Color buttonColors[3]
//     {
//         sf::Color::White,
//         sf::Color(255, 255, 255, 125),
//         sf::Color(255, 255, 255, 125)
//     };

//     int characterSize = 22;
//     float buttonThickness = 1.f;
//     sf::Vector2f wordButtonSize(300, 50);
//     ButtonView::Ptr wordButtonView = std::make_unique<ButtonView>(context, font, text, characterSize, position, wordButtonSize, buttonColors[0]);
//     wordButtonView->setBorderColor(sf::Color(0, 0, 0, 25), buttonThickness);

//     wordButtonView->setOnMouseMoved([sideView, context, buttonColors](EventListener* listener, const sf::Event& event)
//     {
//         ButtonView* button = dynamic_cast<ButtonView*>(listener);
//         if (button->getGlobalBounds().contains(sideView->getSideMouseCoords()))
//         {
//             if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
//                 sf::Mouse::isButtonPressed(sf::Mouse::Right)||
//                 sf::Mouse::isButtonPressed(sf::Mouse::Middle))
//                 button->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
//             else
//                 button->setBackgroundColor(buttonColors[(int)ButtonType::HOVERING]);
//         }
//         else
//             button->setBackgroundColor(buttonColors[(int)ButtonType::NORMAL]);
//     });

//     wordButtonView->setOnMouseButtonPressed([buttonColors](EventListener* listener, const sf::Event& event)
//     {
//         ButtonView* button = dynamic_cast<ButtonView*>(listener);
//         button->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
//     });

//     EventListener::EventDoubleCallback onDoubleCallback = [buttonColors](EventListener* listener, const sf::Event& event, EventListener::EventCallback callback)
//     {
//         ButtonView* button = dynamic_cast<ButtonView*>(listener);
//         button->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
//         callback(listener, event);
//     };

//     wordButtonView->setOnMouseButtonReleased(std::bind(onDoubleCallback, std::placeholders::_1, std::placeholders::_2, callback));

//     const sf::Vector2f textRelativePos(8, 13);
//     wordButtonView->setText(text, textRelativePos);
//     wordButtonView->setTextColor(sf::Color::Black);

//     return std::move(wordButtonView);
// }

WordButtonView::WordButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, SideBackgroundView *sideView)
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
        if (button->getGlobalBounds().contains(sideView->getSideMouseCoords()))
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
    return this->getGlobalBounds().contains(sideView->getSideMouseCoords());
}

bool WordButtonView::isOnMouseButtonReleased(const sf::Event &event) const
{
    return this->getGlobalBounds().contains(sideView->getSideMouseCoords());
}

bool WordButtonView::isOnMouseMoved(const sf::Event &event) const
{
    return true;
}