#ifndef SIDE_VIEW_FACTORY_HPP
#define SIDE_VIEW_FACTORY_HPP

#include <ScrollRectView.hpp>
#include <Activity.hpp>

class SideViewFactory
{
public:
    static ScrollRectView::Ptr create(Activity *publisher, const sf::Vector2f &position);
};

#endif