#ifndef ADD_DEF_BUTTON_FACTORY_HPP
#define ADD_DEF_BUTTON_FACTORY_HPP

#include <EventListener.hpp>
#include <Activity.hpp>
#include <SpriteButtonView.hpp>

class AddDefButtonFactory
{
public:
    static SpriteButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif