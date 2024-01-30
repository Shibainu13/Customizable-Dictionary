#include <SuggestButtonFactory.hpp>

ColoredButtonView::Ptr SuggestButtonFactory::create(Activity *context, const sf::Font &font, const std::string &text, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::Color buttonColors[3]
    {
        sf::Color(249, 249, 249),
        sf::Color(229, 229, 229),
        sf::Color(229, 229, 229)
    };

    sf::Vector2f buttonSize(471, 40);
    unsigned int characterSize = 20;
    ColoredButtonView::Ptr suggestButton = std::make_unique<ColoredButtonView>(context, font, text, characterSize, position, buttonSize, buttonColors);

    constexpr int borderThickness = 2;
    suggestButton->setBorderColor(sf::Color(10, 153, 254), borderThickness);
    suggestButton->setTextColor(sf::Color::Black);

    suggestButton->setOnMouseButtonReleased(callback);

    return std::move(suggestButton);
}