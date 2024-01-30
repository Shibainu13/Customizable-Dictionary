#ifndef RESOURCE_ID_HPP
#define RESOURCE_ID_HPP

#include <ResourceManager.hpp>

enum class TextureID
{
    // definition display
    add_defi,
    edit_defi,

    // header
    app_icon,
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
    dm_sans
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