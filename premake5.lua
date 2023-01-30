-- premake5.lua
workspace "ProtoEngine"
   configurations { "Debug", "Release" }

project "ProtoEngine"
   kind "WindowedApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   links { "glfw" }
   files { "src/**.h", "src/**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"