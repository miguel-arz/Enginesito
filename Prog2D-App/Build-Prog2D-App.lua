project "Prog2D-App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

	  -- Include Core
	  "../Prog2D-RayLib/Source"
   }

   links
   {
      "Prog2D-RayLib"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "WIN32","_DEBUG","_CONSOLE","PLATFORM_DESKTOP", "_CRT_SECURE_NO_WARNINGS" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE", "WIN32","NDEBUG","_CONSOLE","PLATFORM_DESKTOP", "_CRT_SECURE_NO_WARNINGS"}
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "RELEASE", "WIN32","NDEBUG","_CONSOLE","PLATFORM_DESKTOP", "_CRT_SECURE_NO_WARNINGS"}
       runtime "Release"
       optimize "On"
       symbols "Off"