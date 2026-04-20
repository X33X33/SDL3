#include "SDL3_PLUS.hpp"
#include <iostream>

#ifdef HAS_SDL3_IMAGE
#include <SDL3_image/SDL_image.h>
#endif

Sprite::Sprite(SDL_Renderer* renderer, const std::string& filePath)
{
    if (!renderer)
    {
        std::cerr << "Erreur : Renderer invalide pour Sprite\n";
        return;
    }

    SDL_Surface* surface = nullptr;

#ifdef HAS_SDL3_IMAGE
    // Chargement multi-format avec SDL3_image (PNG, JPG, BMP, ...)
    surface = IMG_Load(filePath.c_str());
#else
    // Fallback sans SDL3_image: BMP uniquement
    surface = SDL_LoadBMP(filePath.c_str());
#endif

    if (!surface)
    {
        std::cerr << "Image load error: " << SDL_GetError() << " (" << filePath << ")\n";
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!m_texture)
    {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << "\n";
        return;
    }

    // Récupère les dimensions originales de la texture
    float w, h;
    SDL_GetTextureSize(m_texture, &w, &h);


    m_rect = { 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) };
    m_initialRect = {m_rect.w, m_rect.h};
    m_origin = { m_rect.w / 2.0f, m_rect.h / 2.0f };   // centre par défaut
}
Sprite::~Sprite()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}


#pragma region Getter and Setter
SDL_Texture *Sprite::GetTexture() const
{
    return m_texture; 
}
SDL_FRect Sprite::GetRect() const
{
    return m_rect; 
}
const SDL_FPoint &Sprite::GetPosition(void)
{
    return {m_rect.x, m_rect.y};
}

float Sprite::GetRotation() const
{
    return m_rotation;
}

float Sprite::GetScale() const
{
    return m_scale;
}


SDL_FPoint Sprite::GetOrigin(void)
{
    return {m_rect.x, m_rect.y};
}

void Sprite::SetPosition(float _x, float _y)
{
    m_rect.x = _x;
    m_rect.y = _y;
}

void Sprite::SetPosition(const SDL_FPoint& _position)
{
    m_rect.x = _position.x;
    m_rect.y = _position.y;
}


void Sprite::SetScale(float _width, float _height)
{
    m_rect.w = _width;
    m_rect.h = _height;
}


void Sprite::SetRotation(float _angle)
{
    m_rotation = _angle;
}

void Sprite::SetAlpha(Uint8 _alpha)
{
    m_alpha = _alpha;
    if (m_texture)
    {
        SDL_SetTextureAlphaMod(m_texture, _alpha);
    }
}

void Sprite::SetOrigin(float x, float y)
{
    m_origin.x = x;
    m_origin.y = y;
}

void Sprite::SetOriginCenter()
{
    m_origin =
    { 
        m_rect.w / 2.0f, 
        m_rect.h / 2.0f 
    };
}

void Sprite::SetColorMod(Uint8 r, Uint8 g, Uint8 b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    if (m_texture)
        SDL_SetTextureColorMod(m_texture, r, g, b);
}
#pragma endregion

void Sprite::Move(float offsetX, float offsetY)
{
    m_rect.x += offsetX;
    m_rect.y += offsetY;
}

void Sprite::Rotate(float angleOffset)
{
    m_rotation += angleOffset;
}


void Sprite::Draw(SDL_Renderer* renderer) const
{
    if (!m_texture || !renderer)
    {
        return;  
    } 

    SDL_FRect destRect = m_rect;

    // Appliquer le scale (si tu veux le gérer dynamiquement)
    // destRect.w *= m_scale;
    // destRect.h *= m_scale;

    SDL_RenderTextureRotated
    (
        renderer,
        m_texture,
        nullptr,           // sourceRect = toute la texture
        &destRect,
        m_rotation,
        &m_origin,         // centre de rotation
        SDL_FLIP_NONE
    );
}