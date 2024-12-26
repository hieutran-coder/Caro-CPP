cmake_minimum_required(VERSION 3.5)

project(Caro_Mock_Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Caro_Mock_Project main.cpp
    player.h player.cpp
    match.h match.cpp
    build/Desktop_x86_darwin_generic_mach_o_64bit-Debug/players.txt
    filehandlingexception.h filehandlingexception.cpp
    build/Desktop_x86_darwin_generic_mach_o_64bit-Debug/guild.txt
    build/Desktop_x86_darwin_generic_mach_o_64bit-Debug/match.txt
    bot.h bot.cpp
    filemanager.h filemanager.cpp
    display.h display.cpp
    playermanager.h playermanager.cpp
    caro.h caro.cpp
)

include(GNUInstallDirs)
install(TARGETS Caro_Mock_Project
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
