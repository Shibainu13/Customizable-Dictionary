#ifndef FAV_BUTTON_FACTORY_HPP
#define FAV_BUTTON_FACTORY_HPP

#include <EventListener.hpp>
#include <Activity.hpp>
#include <ColoredButtonView.hpp>
#include <SpriteView.hpp>
#include <TextView.hpp>

class FavButtonFactory
{
public:
    static ColoredButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif