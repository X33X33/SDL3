#ifndef SDL3_PLUS_HPP
#define SDL3_PLUS_HPP

#include <SDL3/SDL.h>
#include <string>

class Sprite
{
public:

    Sprite(SDL_Renderer* renderer, const std::string& filePath);
    ~Sprite();

    #pragma region Getter and Setter
    SDL_Texture* GetTexture() const;
    SDL_FRect GetRect() const;
    SDL_FPoint GetPosition(void);

    float GetRotation() const;
    float GetScale() const;
    SDL_FPoint GetOrigin(void);

    void SetPosition(float _x, float _y);
    void SetPosition(const SDL_FPoint& _position);

    void SetScale(float _width, float _height);
    //void SetScale(float _scaleX, float _scaleY); 

    void SetRotation(float _angle);                 
    void SetAlpha(Uint8 _alpha);                    
    void SetOrigin(float _x, float _y);              
    void SetOriginCenter();                       

    void SetColorMod(Uint8 _r, Uint8 _g, Uint8 _b);  
    #pragma endregion


    // Méthodes pratiques
    void Move(float offsetX, float offsetY);
    void Rotate(float angleOffset);

    // Rendu
    void Draw(SDL_Renderer* renderer) const;

private:

    SDL_Texture* m_texture = nullptr;
    SDL_FRect m_rect = { 0.0f, 0.0f, 0.0f, 0.0f };   // position + taille actuelle
    SDL_FPoint m_initialRect = {0.f, 0.f};
    float m_rotation = 0.0f;                      
    float m_scale = 1.0f;
    Uint8 m_alpha = 255;
    SDL_FPoint m_origin = { 0.0f, 0.0f };         
         
    // Couleur de teinte
    Uint8 m_colorR = 255;
    Uint8 m_colorG = 255;
    Uint8 m_colorB = 255;

    // Désactiver la copie (bonnes pratiques)
    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;
};


#endif //!SDL3_PLUS_HPP