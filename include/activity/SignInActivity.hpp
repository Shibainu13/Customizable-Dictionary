#ifndef SIGN_IN_ACTIVITY_HPP
#define SIGN_IN_ACTIVITY_HPP

#include <Activity.hpp>
#include <ActivityFactory.hpp>
#include <ResourceID.hpp>
#include <AppConfig.hpp>
#include <UserData.hpp>
#include <UserRepo.hpp>
#include <UserSession.hpp>

#include <SpriteView.hpp>
#include <RectangleView.hpp>
#include <TextView.hpp>
#include <SpriteView.hpp>
#include <TextButtonView.hpp>

#include <LoginHyperTextButtonFactory.hpp>
#include <SignInFormFactory.hpp>
#include <SignInButtonFactory.hpp>
#include <LastLoginFactory.hpp>

#include <DictionaryActivity.hpp>

class SignInActivity : public Activity
{
private:
    enum Request
    {
        REQUEST_BUILD_FROM_ORIGIN,
        REQUEST_DESERIALIZE
    };

protected:
    virtual void onEvent(const sf::Event &event) override;
    virtual void onCreate() override;
    virtual void onLoadResource() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    virtual void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt) override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data) override;

private:
    enum AuthState
    {
        SIGN_IN,
        SIGN_UP,
        CHANGE_PASSWORD
    };

private:
    void attachStaticElements();
    void attachSignInBox();
    void attachSignUpBox();
    void attachChangePasswordBox();
    void attachLoginHistory();
    void setAuthState(AuthState state);

private:
    TextureManager mTextureManager;
    FontManager mFontManager;
    SpriteView *signInBoxPtr;
    RectangleView *invisRectPtr;
    AuthState prevState, currentState;
};

#endif