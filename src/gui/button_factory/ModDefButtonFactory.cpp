#include <ModDefButtonFactory.hpp>

SpriteButtonView::Ptr ModDefButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::IntRect textureRects[3]
    {
        sf::IntRect(0, 0, 50, 50),
        sf::IntRect(50, 0, 50, 50),
        sf::IntRect(50, 0, 50, 50)
    };

    sf::Vector2f buttonSize(50, 50);
    SpriteButtonView::Ptr modDefButton = std::make_unique<SpriteButtonView>(context, texture, font, textureRects, "", 0, position, buttonSize);

    modDefButton->setOnMouseButtonReleased(callback);

    return std::move(modDefButton);
}