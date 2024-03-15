#ifndef NEW_DEFI_FACTORY_HPP
#define NEW_DEFI_FACTORY_HPP

#include <EditTextOnScrollView.hpp>
#include <Activity.hpp>

class NewDefiFactory
{
public:
    static EditTextOnScrollView::Ptr create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, ScrollRectView *rectView, EventListener::EventCallback onTextEntered);
};

#endif