#include <SignInButtonFactory.hpp>

ColoredButtonView::Ptr SignInButtonFactory::create(Activity *context, const sf::Font &font, const std::string &text, const sf::Vector2f &position, EventListener::EventCallback onMouseButtonReleased)
{
    const sf::Color buttonColors[3]
    {
        sf::Color(24, 197, 153),
        sf::Color(17, 105, 142),
        sf::Color(17, 105, 142)
    };

    const sf::Vector2f buttonSize(420.f, 54.f);
    unsigned int buttonCharacterSize = 16;
    ColoredButtonView::Ptr button = std::make_unique<ColoredButtonView>(context, font, text, buttonCharacterSize, position, buttonSize, buttonColors);
    button->setTextColor(sf::Color::White);
    button->setCornersRadius(10.f, 4);
    button->setOnMouseButtonReleased(onMouseButtonReleased);

    return std::move(button);
}