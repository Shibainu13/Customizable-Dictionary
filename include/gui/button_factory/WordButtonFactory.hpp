#ifndef WORD_BUTTON_FACTORY_HPP
#define WORD_BUTTON_FACTORY_HPP

#include <EventListener.hpp>
#include <Activity.hpp>
#include <ColoredButtonView.hpp>
#include <TextView.hpp>
#include <SideBackgroundView.hpp>

class WordButtonFactory
{
private:
    enum class ButtonType
    {
        NORMAL,
        HOVERING,
        PRESSED,
        COUNT
    };

public:
    static ButtonView::Ptr create(Activity *context, const sf::Font &font, const std::string &text, const sf::Vector2f &position, SideBackgroundView *sideView, EventListener::EventCallback callback);
};

#endif
