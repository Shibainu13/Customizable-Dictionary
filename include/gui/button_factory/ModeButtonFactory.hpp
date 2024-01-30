#ifndef MODE_BUTTON_FACTORY_HPP
#define MODE_BUTTON_FACTORY_HPP

#include <SpriteButtonView.hpp>
#include <EventListener.hpp>
#include <Activity.hpp>

class ModeButtonFactory
{
public:
    static SpriteButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position);
};

#endif