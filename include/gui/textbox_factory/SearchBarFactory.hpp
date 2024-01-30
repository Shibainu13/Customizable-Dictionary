#ifndef SEARCH_BAR_FACTORY_HPP
#define SEARCH_BAR_FACTORY_HPP

#include <ModeButtonFactory.hpp>
#include <EditTextView.hpp>
#include <EventListener.hpp>
#include <Activity.hpp>
#include <SpriteView.hpp>
#include <TextView.hpp>
#include <RectangleView.hpp>

class SearchBarFactory
{
public:
    static EditTextView::Ptr create(Activity *context, const sf::Font &cursorFont, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback onTextEnterd, EventListener::EventCallback onMouseButtonPressed);
};

#endif