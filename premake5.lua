workspace "magmatis"
   configurations { "Debug", "Release" }

project "magmatis"
   kind "WindowedApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   links { "glfw", "vulkan" }
   files { "src/**.h", "src/**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"