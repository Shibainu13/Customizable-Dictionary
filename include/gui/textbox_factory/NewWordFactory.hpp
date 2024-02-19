#ifndef NEW_WORD_FACTORY_HPP
#define NEW_WORD_FACTORY_HPP

#include <EditTextView.hpp>
#include <Activity.hpp>
#include <EventListener.hpp>

class NewWordFactory
{
public:
    static EditTextView::Ptr create(Activity *publisher, const sf::Font &font, const sf::Vector2f &position);
};

#endif