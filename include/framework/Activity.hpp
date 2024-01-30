#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <SFML/Graphics.hpp>
#include <ViewGroup.hpp>
#include <Intent.hpp>
#include <ActivityManager.hpp>
#include <EventPublisher.hpp>

#include <memory>

class ActivityManager;

class Activity : public ViewGroup, public EventPublisher
{
    friend class ActivityManager;

public:
    typedef std::unique_ptr<Activity> Ptr;

public:
    enum ResultCode
    {
        RESULT_OK,
        RESULT_CANCELED
    };

private:
    ActivityManager *mManager;
    Intent::Ptr mIntent;
    int mResultCode;
    Intent::Ptr mResult;

public:
    Activity();
    virtual ~Activity() override;

    ActivityManager *getActivityManager() const;

    void startActivity(Activity::Ptr activity, Intent::Ptr intent);
    void startActivity(Activity::Ptr activity);

    void finish();
    void setResult(int resultCode, Intent::Ptr data);

protected:
    void initialize();

    virtual void onLoadResource() = 0;
    virtual void onCreate() = 0;
    virtual void onEvent(const sf::Event &event);
    virtual void onEventProcessing();
    virtual void onAttach();
    virtual void onResume();
    virtual void onPause();
    virtual void onDestroy();
    virtual void onDraw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data);

    Intent *getIntent() const;

private:
    void setActivityManager(ActivityManager *manager);
    void setIntent(Intent::Ptr intent);
};

#endif