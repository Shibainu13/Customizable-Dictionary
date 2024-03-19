#ifndef SIGN_IN_ACTIVITY_HPP
#define SIGN_IN_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>
#include <AppConfig.hpp>
#include <UserData.hpp>
#include <UserRepo.hpp>

#include <SpriteView.hpp>
#include <RectangleView.hpp>
#include <TextView.hpp>
#include <SpriteView.hpp>
#include <TextButtonView.hpp>

#include <LoginHyperTextButtonFactory.hpp>
#include <SignInFormFactory.hpp>
#include <SignInButtonFactory.hpp>

class SignInActivity : public Activity
{
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
    void attachStaticElements();
    void attachSignInBox();
    void attachSignUpBox();

private:
    TextureManager mTextureManager;
    FontManager mFontManager;

    SpriteView *signInBoxPtr;
};

#endif