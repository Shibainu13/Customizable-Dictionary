#ifndef ACTIVITY_MANAGER_HPP
#define ACTIVITY_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <ActivityFinishReturn.hpp>
#include <Activity.hpp>
#include <Intent.hpp>
#include <AppConfig.hpp>

#include <stack>
#include <memory>
#include <iostream>

class Activity;

class ActivityManager
{
    friend class Application;

public:
    typedef std::unique_ptr<Activity> ActivityPtr;

private:
    std::stack<ActivityPtr> activityStack;
    sf::RenderWindow mWindow;

public:
    ActivityManager(int windowWidth, int windowHeight, std::string windowTitle);

    void startActivity(ActivityPtr activity, Intent::Ptr intent);
    void attachActivity(ActivityPtr activity);
    void finishActivity(int requestCode, int resultCode, Intent::Ptr data);
    bool isEmpty() const;
    Activity *getCurrentActivity() const;
    sf::RenderWindow &getWindow();

private:
    void clearStack();
    void run();
};

#endif