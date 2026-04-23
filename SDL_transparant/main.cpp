//////////////////////////////////////////////////////////////////////////////
// X33X33 transparent sdl3 project
//
//
//
//////////////////////////////////////////////////////////////////////////////

#include "Utilities/SDL3_PLUS.hpp"
#include "common.hpp"
#include "Utilities/InitialConfiguration/Setup.hpp"
#include "Utilities/FileManipulation.hpp"
#include <filesystem>


struct MainData
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

void MainDataLoad(MainData& _mainData)
{
    std::cout << "App launch\nCurrent files in directory :";
    std::cout << std::filesystem::current_path() << std::endl;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cerr << "Init ok\n";
    
    
    _mainData.window = nullptr;
    _mainData.renderer = nullptr;
    
    const SDL_DisplayMode* desktopMode = SDL_GetDesktopDisplayMode(0);
    //printf("Desktop size x %d, y %d\n", desktopMode->w, desktopMode->h);


    SDL_CreateWindowAndRenderer
    (
        "AudioPlayerX33",
         1920, 1080,
        
        //SDL_WINDOW_BORDERLESS | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_ALWAYS_ON_TOP,
        //Change this if i want border or not, border is beter for debug
        SDL_WINDOW_TRANSPARENT | SDL_WINDOW_ALWAYS_ON_TOP,
        &_mainData.window, &_mainData.renderer
    );

    std::cerr << "Window creation ok\n";
    
    if (!_mainData.window || !_mainData.renderer)
    {
        std::cerr << "Erreur création fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    std::cerr << "MainData load ok\n";



    
}

int main(int argc, char* argv[])
{
    
    
    MainData mainData;
    MainDataLoad(mainData);
    
    SetupWindow();


    //Test
    // SDL_Surface* surface = SDL_LoadBMP(std::string(AssetPath + "sample-bmp.bmp").c_str());

    // if (surface == nullptr)
    // {
    //     std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    //     return 1;
    // }
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(mainData.renderer, surface);


    // if (texture == nullptr)
    // {
    //     std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    //     return 1;
    // }
    // SDL_DestroySurface(surface);


    Sprite spr(mainData.renderer, std::string(AssetPath + "sample-bmp.bmp"));

    spr.SetScale(50.f, 50.f);


    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            running = (event.type == SDL_EVENT_QUIT) ? false : true;
        }

        // Fond complètement transparent
        //SDL_SetRenderDrawColor(mainData.renderer, 0, 0, 0, 0);   // alpha = 0
        SDL_SetRenderDrawColor(mainData.renderer, 0, 0, 0, 0);   // alpha = 0


        SDL_RenderClear(mainData.renderer);

        //SDL_RenderTexture(mainData.renderer, texture, NULL, NULL);
        spr.Draw(mainData.renderer);


        SDL_RenderPresent(mainData.renderer);

        SDL_Delay(16); // ~60 FPS
    }

    spr.~Sprite();

    SDL_DestroyRenderer(mainData.renderer);
    SDL_DestroyWindow(mainData.window);
    SDL_Quit();
    return 0;
}