#include <DelWordButtonFactory.hpp>

SpriteButtonView::Ptr DelWordButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::IntRect buttonRects[3]
    {
        sf::IntRect(0, 0, 20, 20),
        sf::IntRect(20, 0, 20, 20),
        sf::IntRect(20, 0, 20, 20)
    };
    const sf::Vector2f buttonSize(20, 20);
    SpriteButtonView::Ptr delWordButton = std::make_unique<SpriteButtonView>(context, texture, font, buttonRects, "", 0, position, buttonSize);

    delWordButton->setOnMouseButtonReleased(callback);
    return std::move(delWordButton);
}