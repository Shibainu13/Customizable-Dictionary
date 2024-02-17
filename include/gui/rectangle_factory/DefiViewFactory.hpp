#ifndef DEFI_VIEW_FACTORY_HPP
#define DEFI_VIEW_FACTORY_HPP

#include <ScrollRectView.hpp>
#include <Activity.hpp>

class DefiViewFactory
{
public:
    static ScrollRectView::Ptr create(Activity *publisher, const sf::Vector2f &position);
};

#endif