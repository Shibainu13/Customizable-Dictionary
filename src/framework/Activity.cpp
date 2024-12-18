#include <Activity.hpp>

Activity::Activity()
    : mManager(nullptr), mIntent(nullptr), mResultCode(RESULT_CANCELED), mResult(nullptr)
{
}

Activity::~Activity()
{
    mManager = nullptr;
}

void Activity::initialize()
{
    onLoadResource();
    onCreate();
}

ActivityManager *Activity::getActivityManager() const
{
    return mManager;
}

void Activity::setActivityManager(ActivityManager *manager)
{
    mManager = manager;
}

void Activity::startActivity(Activity::Ptr activity, Intent::Ptr intent)
{
    mManager->startActivity(std::move(activity), std::move(intent));
}

void Activity::startActivity(Activity::Ptr activity)
{
    mManager->startActivity(std::move(activity), Intent::Builder().build());
}

void Activity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    ViewGroup::draw(target, states);
    onDraw(target, states);
}

void Activity::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Do nothing
}

void Activity::onEvent(const sf::Event &event)
{
    // Do nothing
}

void Activity::onEventProcessing()
{
    // Do nothing
}

void Activity::onAttach()
{
    // Do nothing
}

void Activity::onResume()
{
    // Do nothing
}

void Activity::onPause()
{
    // Do nothing
}

void Activity::onDestroy()
{
    // Do nothing
}

void Activity::onDraw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Do nothing
}

void Activity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data)
{
    // Do nothing
}

void Activity::finish()
{
    // onPause();
    // onDestroy();
    // mManager->popStack();

    mManager->finishActivity(mIntent->getRequestCode(), mResultCode, std::move(mResult));
}

Intent *Activity::getIntent() const
{
    return mIntent.get();
}

void Activity::setResult(int resultCode, Intent::Ptr data)
{
    mResultCode = resultCode;
    mResult = std::move(data);
}

void Activity::setIntent(Intent::Ptr intent)
{
    mIntent = std::move(intent);
}