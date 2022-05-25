cmake_minimum_required(VERSION 3.1.0)
project(chess)

set(CMAKE_CXX_STANDARD 11)

set(SRC_DIRECTORY src)
set(INCLUDE_DIRECTORY headers)

set(SOURCES
    ${SRC_DIRECTORY}/piece.cpp
    ${SRC_DIRECTORY}/bishop.cpp
    ${SRC_DIRECTORY}/king.cpp
    ${SRC_DIRECTORY}/knight.cpp
    ${SRC_DIRECTORY}/null.cpp
    ${SRC_DIRECTORY}/pawn.cpp
    ${SRC_DIRECTORY}/queen.cpp
    ${SRC_DIRECTORY}/rook.cpp
    ${SRC_DIRECTORY}/templates.cpp
    ${SRC_DIRECTORY}/translate.cpp
    ${SRC_DIRECTORY}/board.cpp
)

include_directories(${INCLUDE_DIRECTORY})
add_executable(${PROJECT_NAME}
    ${SRC_DIRECTORY}/main.cpp
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)