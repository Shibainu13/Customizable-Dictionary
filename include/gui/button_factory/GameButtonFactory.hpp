#ifndef GAME_BUTTON_FACTORY_HPP
#define GAME_BUTTON_FACTORY_HPP

#include <EventListener.hpp>
#include <Activity.hpp>
#include <ColoredButtonView.hpp>
#include <TextView.hpp>
#include <SpriteView.hpp>

class GameButtonFactory
{
public:
    static ColoredButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif