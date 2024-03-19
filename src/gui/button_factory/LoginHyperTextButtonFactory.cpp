#include <LoginHyperTextButtonFactory.hpp>

TextButtonView::Ptr LoginHyperTextButtonFactory::create(Activity *context, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size, EventListener::EventCallback onMouseReleased)
{
    const sf::Color textColors[3]
    {
        sf::Color(66, 133, 244),
        sf::Color(24, 197, 153),
        sf::Color(24, 197, 153)
    };
    unsigned int characterSize = 13;
    TextButtonView::Ptr hyperTextButton = std::make_unique<TextButtonView>(context, font, text, characterSize, position, size, textColors);

    return std::move(hyperTextButton);
}