#ifndef VIEWGROUP_HPP
#define VIEWGROUP_HPP

#include <SFML/Graphics.hpp>

#include <EventListener.hpp>

#include <memory>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <cassert>

class ViewGroup : public sf::Drawable, public sf::Transformable, public EventListener
{
public:
    typedef std::unique_ptr<ViewGroup> Ptr;

public:
    ViewGroup();
    ViewGroup(EventPublisher *publisher);
    virtual ~ViewGroup() = default;

    ViewGroup *getParent() const;
    void setParent(ViewGroup *parent);

    void attachView(ViewGroup::Ptr view);
    ViewGroup::Ptr detachView(const ViewGroup &view);
    void detachAllViews();
    const std::vector<ViewGroup::Ptr> &getViews() const;

    sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

    void unsubscribeAll();

    virtual bool isMarkedForRemoval() const;
    virtual bool isDestroyed() const;

    void setUpdate(bool isUpdate);
    bool isUpdate() const;

    void setVisibility(bool isVisible);
    bool isVisible() const;

    void setIsListeningAll(bool isListening);

    void update(sf::Time delta);

private:
    virtual void updateCurrent(sf::Time delta);
    void updateChildren(sf::Time delta);

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    virtual void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    bool mIsVisible, mIsUpdate;
    ViewGroup *parent;
    std::vector<ViewGroup::Ptr> childViews;
};

#endif