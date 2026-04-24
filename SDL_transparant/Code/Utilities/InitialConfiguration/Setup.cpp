#include "Setup.hpp"

void SetupWindow(void)
{
    #if defined(_WIN32) || defined(_WIN64)
    std::cout << "[Setup] Detected Windows OS. Applying Windows-specific window rules..." << std::endl;
    // TODO: Add Windows-specific window rules if needed


    #elif defined(__linux__)
    std::cout << "[Setup] Detected Linux OS. Checking for Hyprland..." << std::endl;
    
    // Check for Hyprland environment variables
    const char* hyprland_env = std::getenv("HYPRLAND_INSTANCE_SIGNATURE");
    const char* wayland_env = std::getenv("WAYLAND_DISPLAY");
    const char* xdg_env = std::getenv("XDG_CURRENT_DESKTOP");

    if (hyprland_env || (xdg_env && std::string(xdg_env).find("Hyprland") != std::string::npos))
    {
        std::cout << "[Setup] Hyprland detected. Checking configuration..." << std::endl;

        if (!HyprlandIsConfigured())
        {
            std::cout << "[Setup] Hyprland is not configured for full transparency. Attempting to set up..." << std::endl;

            if (!SetupHyprlandConfig()) 
            {
                std::cerr << "[Setup] Failed to configure Hyprland for transparency. Manual intervention may be required." << std::endl;
            } 
            else
            {
                std::cout << "[Setup] Hyprland configuration updated." << std::endl;
            }
        } 
        else
        {
            std::cout << "[Setup] Hyprland is already configured for transparency." << std::endl;
        }
    }
    else
    {

        std::cout << "[Setup] Not running under Hyprland. No compositor-specific setup applied." << std::endl;
    }

    #else

    std::cout << "[Setup] Unknown or unsupported OS. No setup applied." << std::endl;

    #endif
}

bool HyprlandIsConfigured(void)
{
    return false;
} 

bool SetupHyprlandConfig(void)
{
    //Name of executable
    //hyprctl keyword windowrulev2 "noblur,class:^(MyTransparentApp)$"

    return false;
}
