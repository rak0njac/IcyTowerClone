cmake_minimum_required(VERSION 3.22)

project(IcyTowerClone)

set(CMAKE_CXX_STANDARD 11)

include_directories(ICYTOWERCL {YOUR SFML DIRECTORY}/include)

set(SFML_DIR "{YOUR SFML DIRECTORY}/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(IcyTowerClone
        ICYTOWERCL/Animation.cpp
        ICYTOWERCL/Animation.h
        ICYTOWERCL/Background.cpp
        ICYTOWERCL/Background.h
        ICYTOWERCL/Camera.cpp
        ICYTOWERCL/Camera.h
        ICYTOWERCL/Consts.h
        ICYTOWERCL/DefaultFont.cpp
        ICYTOWERCL/DefaultFont.h
        ICYTOWERCL/EyeCandy.cpp
        ICYTOWERCL/EyeCandy.h
        ICYTOWERCL/EyeCandyEngine.cpp
        ICYTOWERCL/EyeCandyEngine.h
        ICYTOWERCL/FloorTypes.cpp
        ICYTOWERCL/FloorTypes.h
        ICYTOWERCL/Game.cpp
        ICYTOWERCL/Game.h
        ICYTOWERCL/GameOver.cpp
        ICYTOWERCL/GameOver.h
        ICYTOWERCL/Icon.c
        ICYTOWERCL/Layer.cpp
        ICYTOWERCL/Layer.h
        ICYTOWERCL/main.cpp
        ICYTOWERCL/PitchedSound.cpp
        ICYTOWERCL/PitchedSound.h
        ICYTOWERCL/Platform.cpp
        ICYTOWERCL/Platform.h
        ICYTOWERCL/PlatformEngine.cpp
        ICYTOWERCL/PlatformEngine.h
        ICYTOWERCL/Player.cpp
        ICYTOWERCL/Player.h
        ICYTOWERCL/RainbowText.cpp
        ICYTOWERCL/RainbowText.h
        ICYTOWERCL/resource.h
        ICYTOWERCL/Score.cpp
        ICYTOWERCL/Score.h
        ICYTOWERCL/Timer.cpp
        ICYTOWERCL/Timer.h)

target_link_libraries(IcyTowerClone sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
