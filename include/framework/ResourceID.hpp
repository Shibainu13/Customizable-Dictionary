#ifndef RESOURCE_ID_HPP
#define RESOURCE_ID_HPP

#include <ResourceManager.hpp>

enum class TextureID
{
    app_icon,

    // definition display
    add_defi,
    edit_defi,
    add_fav,
    confirm,
    cancel,

    // header
    dictionary_icon,
    daily_icon,
    favorite_icon,
    game_icon,
    lang_arrow,
    search_icon,
    logout,
    mode_config,

    // sidebar
    edit_dict,
    del_word,
    remove_word,

    // login
    saly_mark,
    profile,
    x_vec,
    shaded_rect
};

enum class ImageID
{
};

enum class FontID
{
    font_awesome,
    serif,
    open_sans,
    frank_ruhl,
    dm_sans,
    poppins_light,
    poppins_medium,
    poppins_semibold,
    poppins_regular
};

enum class SoundBufferID
{
};

enum class MusicID
{
};

typedef ResourceManager<sf::Texture, TextureID> TextureManager;
typedef ResourceManager<sf::Image, ImageID> ImageManager;
typedef ResourceManager<sf::Font, FontID> FontManager;
typedef ResourceManager<sf::SoundBuffer, SoundBufferID> SoundBufferManager;

#endif