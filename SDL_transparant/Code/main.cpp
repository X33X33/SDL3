//////////////////////////////////////////////////////////////////////////////
// X33X33 transparent sdl3 project
//
//
//
//////////////////////////////////////////////////////////////////////////////

#include "Utilities/SDL3_PLUS.hpp"
//#include "common.hpp"
#include "Utilities/InitialConfiguration/Setup.hpp"
//#include "Utilities/FileManipulation.hpp"
#include "AudioPlayer/AudioPlayer.hpp"
#include <SDL3/SDL_stdinc.h>
#include <filesystem>

#if defined(_WIN32)
    #include <process.h>
    #define GETPID _getpid
#else
    #include <unistd.h>
    #define GETPID getpid
#endif

std::string AssetPath = "../Assets/";

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
        500, 300,
        
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

    //Random init
    printf("PID: %d\n", GETPID());
    srand((unsigned int)(GETPID()));

    std::cerr << "MainData load ok\n";    
}

int main(int argc, char* argv[])
{    
    MainData mainData;
    MainDataLoad(mainData);
    
    SetupWindow();

    AudioPlayer audioPlayer;


    Sprite spr(mainData.renderer, std::string(AssetPath + "sample-bmp.bmp"));

    //spr.SetScale(50.f, 50.f);


    bool running = true;
    SDL_Event event;

    while (running)
    {
        //Poll event
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:

                    running = false;
                    break;
            }
        }

        //Update
        audioPlayer.Update(0.f);
        

        //Draw
        SDL_SetRenderDrawColor(mainData.renderer, 0, 0, 0, 0);
        SDL_RenderClear(mainData.renderer);

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