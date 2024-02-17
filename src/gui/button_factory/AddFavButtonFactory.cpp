#include <AddFavButtonFactory.hpp>

ToggleButtonView::Ptr AddFavButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::IntRect textureRects[3]
    {
        sf::IntRect(0, 0, 24, 22),
        sf::IntRect(0, 0, 24, 22),
        sf::IntRect(0, 0, 24, 22)
    };

    sf::Vector2f buttonSize(40, 40);
    sf::Vector2f textureSize(24, 22);
    ToggleButtonView::Ptr saveIndicator = std::make_unique<ToggleButtonView>(context, texture, font, textureRects, "", 0, position, buttonSize, textureSize);
    saveIndicator->setCircleButton();
    saveIndicator->setBorderColor(sf::Color::White, 2.f);

    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener* listener, const sf::Event& event, EventListener::EventCallback callback)
    {
        ToggleButtonView* button = dynamic_cast<ToggleButtonView*>(listener);
        if (button->getState())
            button->setBorderColor(sf::Color(22, 199, 154), BORDER_WIDTH);
        else
            button->setBorderColor(sf::Color::White, BORDER_WIDTH);
        callback(listener, event);
    };

    saveIndicator->setOnMouseButtonReleased(std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, callback));

    return std::move(saveIndicator);
}