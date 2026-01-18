cmake_minimum_required(VERSION 3.29)
project(WallpaperAerialsExtensionFix)

set(CMAKE_CXX_STANDARD 20)

# Set the project to be a macOS application bundle
set(CMAKE_MACOSX_BUNDLE TRUE)
set(CMAKE_MACOSX_BUNDLE_GUI_APP FALSE)

# Specify that we want to create a universal binary
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

add_executable(WallpaperAerialsExtensionFix MACOSX_BUNDLE main.cpp)

# Link against the necessary macOS frameworks
target_link_libraries(WallpaperAerialsExtensionFix
        "-framework CoreFoundation"
        "-framework CoreServices"
        "-framework ApplicationServices"
)


set_target_properties(WallpaperAerialsExtensionFix PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.padya.WallpaperAerialsExtensionFix"
    MACOSX_BUNDLE_BUNDLE_VERSION "1.1.0"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "1.1"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
)
