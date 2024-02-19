#include <NewDefiButtonFactory.hpp>

ColoredButtonView::Ptr NewDefiButtonFactory::create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, EventListener::EventCallback onMouseReleased)
{
    const sf::Color buttonColors[3]
    {
        sf::Color(217, 217, 217),
        sf::Color(190, 190, 190),
        sf::Color(190, 190, 190)
    };
    const sf::Vector2f newDefiButtonSize(890.f, 27.f);
    ColoredButtonView::Ptr newDefiButton = std::make_unique<ColoredButtonView>(publisher, font, text, position, newDefiButtonSize, buttonColors);
    newDefiButton->setBorderColor(sf::Color::Black, 0.2);
    newDefiButton->setOnMouseButtonReleased(onMouseReleased);

    return std::move(newDefiButton);
}