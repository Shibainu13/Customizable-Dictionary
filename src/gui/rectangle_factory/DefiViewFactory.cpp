#include <DefiViewFactory.hpp>

ScrollRectView::Ptr DefiViewFactory::create(Activity *publisher, const sf::Vector2f &position)
{
    const sf::Vector2f defiViewSize(950.f, 1000.f);
    const sf::Color defiViewColor(sf::Color::White);
    const sf::FloatRect viewRect(330.f, 222.f, 950, 458);
    ScrollRectView::Ptr defiView = std::make_unique<ScrollRectView>(publisher, defiViewSize, position, defiViewColor, viewRect);
    defiView->setViewPort(sf::FloatRect(0.257, 0.308, 0.742, 0.795));
    defiView->setCenter(805.f, 451.f);

    return std::move(defiView);
}