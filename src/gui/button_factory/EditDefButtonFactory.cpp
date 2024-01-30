#include <EditDefButtonFactory.hpp>

SpriteButtonView::Ptr EditDefButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::IntRect textureRects[3]
    {
        sf::IntRect(0, 0, 21, 20),
        sf::IntRect(21, 0, 21, 20),
        sf::IntRect(21, 0, 21, 20)
    };

    sf::Color borderColors[3]
    {
        sf::Color::White,
        sf::Color(255, 255, 255, 150),
        sf::Color(255, 255, 255, 150)
    };

    sf::Vector2f buttonSize(40, 40);
    SpriteButtonView::Ptr editDefButtonView = std::make_unique<SpriteButtonView>(context, texture, font, textureRects, "", 0, position, buttonSize, borderColors);
    editDefButtonView->setCircleButton();
    editDefButtonView->setOnMouseButtonReleased(callback);

    return std::move(editDefButtonView);
}