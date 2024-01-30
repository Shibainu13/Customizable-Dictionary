#include <WordButtonFactory.hpp>

ButtonView::Ptr WordButtonFactory::create(Activity *context, const sf::Font &font, const std::string &text, const sf::Vector2f &position, SideBackgroundView* sideView, EventListener::EventCallback callback)
{
    sf::Color buttonColors[3]
    {
        sf::Color::White,
        sf::Color(255, 255, 255, 125),
        sf::Color(255, 255, 255, 125)
    };

    int characterSize = 22;
    float buttonThickness = 1.f;
    sf::Vector2f wordButtonSize(300, 50);
    ButtonView::Ptr wordButtonView = std::make_unique<ButtonView>(context, font, text, characterSize, position, wordButtonSize, buttonColors[0]);
    wordButtonView->setBorderColor(sf::Color(0, 0, 0, 25), buttonThickness);

    wordButtonView->setOnMouseMoved([sideView, context, buttonColors](EventListener* listener, const sf::Event& event)
    {
        ButtonView* button = dynamic_cast<ButtonView*>(listener);
        if (button->getGlobalBounds().contains(sideView->getSideMouseCoords()))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Right)||
                sf::Mouse::isButtonPressed(sf::Mouse::Middle))
                button->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
            else
                button->setBackgroundColor(buttonColors[(int)ButtonType::HOVERING]);
        }
        else
            button->setBackgroundColor(buttonColors[(int)ButtonType::NORMAL]);
    });

    wordButtonView->setOnMouseButtonPressed([buttonColors](EventListener* listener, const sf::Event& event)
    {
        ButtonView* button = dynamic_cast<ButtonView*>(listener);
        button->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
    });

    EventListener::EventDoubleCallback onDoubleCallback = [buttonColors](EventListener* listener, const sf::Event& event, EventListener::EventCallback callback)
    {
        ButtonView* button = dynamic_cast<ButtonView*>(listener);
        button->setBackgroundColor(buttonColors[(int)ButtonType::PRESSED]);
        callback(listener, event);
    };

    wordButtonView->setOnMouseButtonReleased(std::bind(onDoubleCallback, std::placeholders::_1, std::placeholders::_2, callback));

    const sf::Vector2f textRelativePos(8, 13);
    wordButtonView->setText(text, textRelativePos);
    wordButtonView->setTextColor(sf::Color::Black);

    return std::move(wordButtonView);
}