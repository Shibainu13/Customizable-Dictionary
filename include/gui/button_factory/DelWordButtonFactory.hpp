#ifndef DEL_WORD_BUTTON_FACTORY
#define DEL_WORD_BUTTON_FACTORY

#include <SpriteButtonView.hpp>
#include <Activity.hpp>
#include <EventListener.hpp>

class DelWordButtonFactory
{
public:
    static SpriteButtonView::Ptr create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif