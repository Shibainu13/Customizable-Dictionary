#ifndef NEW_DEFI_BUTTON_FACTORY_HPP
#define NEW_DEFI_BUTTON_FACTORY_HPP

#include <ColoredButtonView.hpp>
#include <Activity.hpp>

class NewDefiButtonFactory
{
public:
    static ColoredButtonView::Ptr create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, EventListener::EventCallback onMouseReleased);
};

#endif