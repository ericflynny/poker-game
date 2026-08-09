cmake_minimum_required(VERSION 3.16)
project(PokerMachineGUI CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLTK REQUIRED)

add_executable(poker_gui
    src/main.cpp
    src/CardView.cpp
    src/PayoutBanner.cpp
    src/BetSelector.cpp
    src/CoinSlot.cpp
    src/PokerMachineWindow.cpp
)

target_include_directories(poker_gui PRIVATE ${FLTK_INCLUDE_DIR} src)
target_link_libraries(poker_gui PRIVATE ${FLTK_LIBRARIES})
