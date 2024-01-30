#ifndef ADD_FAV_BUTTON_FACTORY_HPP
#define ADD_FAV_BUTTON_FACTORY_HPP

#include <EventListener.hpp>
#include <Activity.hpp>
#include <ToggleButtonView.hpp>
#include <SpriteView.hpp>

class AddFavButtonFactory
{
private:
    static constexpr int BORDER_WIDTH = 2.f;

public:
    static ToggleButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif