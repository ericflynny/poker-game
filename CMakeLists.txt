cmake_minimum_required(VERSION 3.16)
project(PokerMachineGUI CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLTK REQUIRED)

file(GLOB BACKEND_SOURCES CONFIGURE_DEPENDS src/backend/*.cpp)
file(GLOB GUI_SOURCES CONFIGURE_DEPENDS src/gui/*.cpp)

add_executable(poker_gui
    ${GUI_SOURCES}
    ${BACKEND_SOURCES}
)

target_include_directories(poker_gui PRIVATE ${FLTK_INCLUDE_DIR} src/gui src/backend)
target_link_libraries(poker_gui PRIVATE ${FLTK_LIBRARIES})
