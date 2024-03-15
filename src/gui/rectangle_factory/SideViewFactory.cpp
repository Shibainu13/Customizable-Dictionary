#include <SideViewFactory.hpp>

ScrollRectView::Ptr SideViewFactory::create(Activity *publisher, const sf::Vector2f &position)
{
    const sf::Vector2f sideViewSize(330.f, 3000.f);
    const sf::Color sideViewColor(sf::Color(237, 237, 237));
    const sf::FloatRect viewRect(0, 0, 330, 650);
    ScrollRectView::Ptr sideView = std::make_unique<ScrollRectView>(publisher, sideViewSize, position, sideViewColor, viewRect);
    sideView->setViewPort(sf::FloatRect(0, 0.159, 0.257, 0.841));
    sideView->setCenter(165.f, 400.f);
    sideView->setOutineColor(sf::Color::Black);
    sideView->setOutlineThickness(0.2f);

    return std::move(sideView);
}