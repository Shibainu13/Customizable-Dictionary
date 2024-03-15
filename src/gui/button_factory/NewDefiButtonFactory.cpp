#include <NewDefiButtonFactory.hpp>

WordButtonView::Ptr NewDefiButtonFactory::create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, ScrollRectView *rectView, EventListener::EventCallback onMouseReleased)
{
    const sf::Color buttonColors[3]
    {
        sf::Color(217, 217, 217),
        sf::Color(190, 190, 190),
        sf::Color(190, 190, 190)
    };
    const sf::Vector2f newDefiButtonSize(890.f, 27.f);
    WordButtonView::Ptr newDefiButton = std::make_unique<WordButtonView>(publisher, font, text, 20, position, newDefiButtonSize, buttonColors, rectView);
    // newDefiButton->setBorderColor(sf::Color::Black, 0.2);
    newDefiButton->setOnMouseButtonReleased(onMouseReleased);
    newDefiButton->setText(text, sf::Vector2f(10.f, 2.f));
    newDefiButton->setTextColor(sf::Color(0, 0, 0, 100.f));

    return std::move(newDefiButton);
}