require "cmake"


workspace "KitsuneCalculator"
configurations {"Debug"}
startproject "App"
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "src/vendor/imgui"


project "App"
    kind "ConsoleApp"
    language "C++"
    files {"src/app**h","src/app/**.cpp"}


    staticruntime "On"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-int/" .. outputDir .. "/%{prj.name}")

    includedirs {
        "src/vendor/glfw/include",
        "src/vendor/imgui/backends",
        "src/vendor/imgui",
    }
    
    links{
        "ImGui",
        "X11",
        "glfw",
        "GL"
    }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

