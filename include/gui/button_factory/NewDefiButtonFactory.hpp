#ifndef NEW_DEFI_BUTTON_FACTORY_HPP
#define NEW_DEFI_BUTTON_FACTORY_HPP

#include <WordButtonView.hpp>
#include <Activity.hpp>

class NewDefiButtonFactory
{
public:
    static WordButtonView::Ptr create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, ScrollRectView *rectView, EventListener::EventCallback onMouseReleased);
};

#endif