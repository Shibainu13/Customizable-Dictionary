#ifndef EDIT_DEF_BUTTON_FACTORY_HPP
#define EDIT_DEF_BUTTON_FACTORY_HPP

#include <EventListener.hpp>
#include <SpriteButtonView.hpp>
#include <Activity.hpp>

class EditDefButtonFactory
{
public:
    static SpriteButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif