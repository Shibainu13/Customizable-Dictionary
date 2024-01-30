#ifndef SUGGEST_BUTTON_FACTORY_HPP
#define SUGGEST_BUTTON_FACTORY_HPP

#include <ColoredButtonView.hpp>
#include <Activity.hpp>
#include <EventListener.hpp>

class SuggestButtonFactory
{
public:
    static ColoredButtonView::Ptr create(Activity *context, const sf::Font &font, const std::string &text, const sf::Vector2f &position, EventListener::EventCallback callback);
};

#endif