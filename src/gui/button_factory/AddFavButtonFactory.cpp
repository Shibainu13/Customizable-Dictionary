#include <AddFavButtonFactory.hpp>

ToggleButtonView::Ptr AddFavButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::IntRect textureRects[2]
    {
        sf::IntRect(0, 0, 24, 22),
        sf::IntRect(0, 0, 24, 22)
    };

    sf::Color borderColors[2]
    {
        sf::Color::White,
        sf::Color(22, 199, 154)
    };

    sf::Vector2f buttonSize(40, 40);
    sf::Vector2f textureSize(24, 22);
    ToggleButtonView::Ptr saveIndicator = std::make_unique<ToggleButtonView>(context, texture, font, textureRects, "", 0, position, buttonSize, textureSize, borderColors);
    saveIndicator->setCircleButton();
    saveIndicator->setOnMouseButtonReleased(callback);
    saveIndicator->setState(false);

    return std::move(saveIndicator);
}