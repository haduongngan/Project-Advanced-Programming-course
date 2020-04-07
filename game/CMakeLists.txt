cmake_minimum_required(VERSION 3.15)
project(game)
set(CMAKE_CXX_STANDARD 14)

add_executable(game main.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /Users/hatnho0708/Documents/SDL/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(game LINK_PUBLIC ${SDL2_LIBRARY})
target_link_libraries(game LINK_PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(game LINK_PUBLIC ${SDL2_TTF_LIBRARIES})
target_link_libraries(game LINK_PUBLIC ${SDL2_MIXER_LIBRARIES})
