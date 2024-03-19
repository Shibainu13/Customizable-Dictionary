#ifndef LOGIN_HYPER_TEXT_BUTTON_FACTORY_HPP
#define LOGIN_HYPER_TEXT_BUTTON_FACTORY_HPP

#include <TextButtonView.hpp>
#include <Activity.hpp>
#include <EventListener.hpp>

class LoginHyperTextButtonFactory
{
public:
    static TextButtonView::Ptr create(Activity *context, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size, EventListener::EventCallback onMouseReleased);
};

#endif