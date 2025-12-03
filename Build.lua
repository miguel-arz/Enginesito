-- premake5.lua
workspace "Prog2D"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Prog2D-App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Prog2D-RayLib"
	include "Prog2D-RayLib/Build-Prog2D-RayLib.lua"
group ""

include "Prog2D-App/Build-Prog2D-App.lua"