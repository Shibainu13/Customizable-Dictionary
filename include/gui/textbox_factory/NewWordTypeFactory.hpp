#ifndef NEW_WORD_TYPE_FACTORY_HPP
#define NEW_WORD_TYPE_FACTORY_HPP

#include <EditTextOnScrollView.hpp>
#include <ScrollRectView.hpp>
#include <Activity.hpp>

class NewWordTypeFactory
{
public:
    static EditTextOnScrollView::Ptr create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, ScrollRectView *scrollRect);
};

#endif