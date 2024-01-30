#include <ViewGroup.hpp>

ViewGroup::ViewGroup()
    : parent(nullptr), mIsVisible(true), mIsUpdate(true)
{
}

ViewGroup::ViewGroup(EventPublisher *publisher)
    : EventListener(publisher), parent(nullptr), mIsVisible(true), mIsUpdate(true)
{
}

ViewGroup *ViewGroup::getParent() const
{
    return parent;
}

void ViewGroup::setParent(ViewGroup *parent)
{
    this->parent = parent;
}

void ViewGroup::attachView(ViewGroup::Ptr view)
{
    view->setParent(this);
    childViews.push_back(std::move(view));
}

ViewGroup::Ptr ViewGroup::detachView(const ViewGroup &view)
{
    auto found = std::find_if(childViews.begin(), childViews.end(), [&](ViewGroup::Ptr &p) -> bool
    { 
        return p.get() == &view; 
    });

    assert((found != childViews.end()) && "ViewGroup::detachView - Child view not found.\n");

    ViewGroup::Ptr result = std::move(*found);
    result->setParent(nullptr);
    result->unsubscribeAll();
    childViews.erase(found);
    return std::move(result);
}

void ViewGroup::detachAllViews()
{
    for (auto &view : childViews)
    {
        view->setParent(nullptr);
        view->unsubscribeAll();
    }
    childViews.clear();
}

const std::vector<ViewGroup::Ptr> &ViewGroup::getViews() const
{
    return childViews;
}

void ViewGroup::unsubscribeAll()
{
    unsubscribe();
    for (auto &child : childViews)
        child->unsubscribeAll();
}

void ViewGroup::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!isVisible())
        return;

    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}

void ViewGroup::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
     for (auto &child : childViews)
        child->draw(target, states);
}

void ViewGroup::updateCurrent(sf::Time delta)
{
    // ...
}

void ViewGroup::update(sf::Time delta)
{
    if (isUpdate())
    {
        updateCurrent(delta);
        updateChildren(delta);
    }
}

void ViewGroup::updateChildren(sf::Time delta)
{
    for (auto &child : childViews)
        child->update(delta);
}

sf::Vector2f ViewGroup::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform ViewGroup::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const ViewGroup *node = this; node != nullptr; node = node->parent)
        transform = node->getTransform() * transform;

    return transform;
}

bool ViewGroup::isMarkedForRemoval() const
{
    return isDestroyed();
}

// by default views don't need to be destroyed
bool ViewGroup::isDestroyed() const
{
    return false;
}

void ViewGroup::setUpdate(bool isUpdate)
{
    mIsUpdate = isUpdate;
}

bool ViewGroup::isUpdate() const
{
    return mIsUpdate;
}

void ViewGroup::setVisibility(bool isVisible)
{
    mIsVisible = isVisible;
}

bool ViewGroup::isVisible() const
{
    return mIsVisible;
}

void ViewGroup::setIsListeningAll(bool isListening)
{
    setIsListening(isListening);
    for (auto &child : childViews)
        child->setIsListening(isListening);
}
