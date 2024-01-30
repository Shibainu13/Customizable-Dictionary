#ifndef EDIT_DICT_BUTTON_FACTORY_HPP
#define EDIT_DICT_BUTTON_FACTORY_HPP

#include <EventListener.hpp>
#include <Activity.hpp>
#include <SpriteButtonView.hpp>

class EditDictButtonFactory
{
public:
    static SpriteButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif