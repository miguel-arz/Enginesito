project "Prog2D-RayLib"
   kind "StaticLib"
   language "C"
   cdialect "C17"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"
   files { "Source/**.h", "Source/**.cpp", "Source/**.c", "Source/**.hpp", "Source/**.cxx"}
   
   includedirs
   {
      "Source", "external"
   }

   links 
   {
       "opengl32",
       "kernel32",
       "user32",
       "gdi32",
       "winmm",
       "winspool",
       "comdlg32",
       "advapi32",
       "shell32",
       "ole32",
       "oleaut32",
       "uuid",
       "odbc32",
       "odbccp32"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

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
       defines { "DIST", "WIN32","NDEBUG","_CONSOLE","PLATFORM_DESKTOP", "_CRT_SECURE_NO_WARNINGS"}
       runtime "Release"
       optimize "On"
       symbols "Off"

    filter {"system:windows", "files:Source/Prog2D-Raylib/platforms/**.*"}
        flags {"ExcludeFromBuild"}