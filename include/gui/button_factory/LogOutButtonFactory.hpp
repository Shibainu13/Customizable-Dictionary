#ifndef LOG_OUT_BUTTON_FACTORY_HPP
#define LOG_OUT_BUTTON_FACTORY_HPP

#include <SpriteButtonView.hpp>
#include <EventListener.hpp>
#include <Activity.hpp>

class LogOutButtonFactory
{
public:
    static SpriteButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif